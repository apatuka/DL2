// net_transport.h - Transporte abstracto que sustituye a CGNET.DLL (wrapper de DirectPlay) en el port.
//
// El original usa 18 funciones CGNet_* / CGNetService_* / CGNetSession_* / CGNetPlayer_* / CGNetMessage_*
// (ver docs/NETWORK.md §5).  Toda la lógica de sesión (src/game/net_session.cpp) habla con esta
// interfaz; SDL_net / ENet implementarán NetTransport más adelante.  Aquí sólo hay:
//   - NetTransport: interfaz virtual (sesiones, jugadores, envío garantizado, recepción).
//   - LoopbackTransport: implementación en proceso (colas FIFO) para tests y partidas locales.
//
// Semántica exigida por el protocolo (igual que DirectPlay "guaranteed"):
//   - send()/broadcast() son fiables y conservan el orden entre un par de peers.
//   - broadcast() entrega a todos los jugadores de la sesión MENOS al emisor.
//   - poll() devuelve mensajes de datos (NetEvent::Data) y avisos de desconexión (NetEvent::PlayerLeft,
//     equivalente a CGNetMessage_GetInfo() == 3, con `from` = jugador que se fue).
//   - Los ids de peer (uint32_t) son los "handles de jugador" de CGNet: viajan en la cápsula (+4) y el
//     maestro los guarda por índice de jugador (NetState::peerHandle[]).  0 = ninguno.
#pragma once
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <span>
#include <string>
#include <vector>

namespace dl2::net {

enum class NetEvent : uint8_t {
    Data       = 1,   // CGNetMessage_GetInfo == 1: mensaje de datos (buffer de 0x5c bytes)
    PlayerLeft = 3,   // CGNetMessage_GetInfo == 3: un jugador ha abandonado la sesión
};

struct NetMessage {
    NetEvent             kind = NetEvent::Data;
    uint32_t             from = 0;      // peer emisor (handle CGNet); en PlayerLeft: el que se fue
    std::vector<uint8_t> data;          // sólo en Data
};

struct NetPeerInfo {
    uint32_t    id = 0;
    std::string name;                   // "Deadlock 2 Host", "Closed Deadlock 2 Host", "Deadlock 2 Player"
};

// Máscara de servicios (FUN_00458138 / DAT_004d5a50 gNetJoined): CGNetService_GetType 4->1, 3->2, 1->4, 2->8
enum NetService : uint32_t {
    kServiceModem  = 1,   // CGNetService_GetType() == 4
    kServiceSerial = 2,   // == 3
    kServiceIPX    = 4,   // == 1
    kServiceTCP    = 8,   // == 2
};

class NetTransport {
public:
    virtual ~NetTransport() = default;

    // CGNet_Initialize + CGNet_FindServices (FUN_00457dbc)
    virtual bool     initialize() = 0;
    // CGNet_Cleanup (FUN_00458298)
    virtual void     shutdown() = 0;
    // máscara NetService de los servicios disponibles (FUN_00458138)
    virtual uint32_t services() const = 0;
    // elige el servicio (FUN_004581a8); kind es UNA de las máscaras NetService
    virtual bool     selectService(uint32_t kind) = 0;
    // CGNetService_ConnectToIPAddress (FUN_00458508); -0x85 del original -> false + mensaje de DirectX
    virtual bool     connectToAddress(const char* address) { (void)address; return true; }

    // CGNetService_CreateSession(name, maxPlayers=7) (FUN_004582e0)
    virtual bool     hostSession(const char* name, int maxPlayers) = 0;
    // CGNetService_FindSessions + CGNetSession_GetName (FUN_004583ac): rellena hasta 20 nombres
    virtual int      findSessions(std::vector<std::string>& names) = 0;
    // CGNetSession_Join(sessions[index]) (FUN_00458434)
    virtual bool     joinSession(int index) = 0;
    // CGNetSession_DisableJoin (FUN_00458384): la sesión deja de admitir jugadores
    virtual void     disableJoin() {}
    // CGNetSession_CreatePlayer(name) -> id del peer local (0 = error)
    virtual uint32_t createPlayer(const char* name) = 0;
    // CGNetSession_FindPlayers + CGNetPlayer_GetName
    virtual int      findPlayers(std::vector<NetPeerInfo>& out) = 0;

    // CGNetPlayer_SendMessageGuaranteed(local, toPeer, buf, 0x5c)
    virtual bool     send(uint32_t toPeer, std::span<const uint8_t> data) = 0;
    // CGNetPlayer_BroadcastMessageGuaranteed(local, buf, 0x5c): a todos menos a mí
    virtual bool     broadcast(std::span<const uint8_t> data) = 0;
    // CGNetPlayer_GetMessage: false si no hay nada pendiente
    virtual bool     poll(NetMessage& out) = 0;

    virtual uint32_t localPeer() const = 0;
};

// ----------------------------------------------------------------------------------------
// LoopbackTransport: varios peers en el mismo proceso comparten un LoopbackHub.
// ----------------------------------------------------------------------------------------
class LoopbackHub {
public:
    struct Peer {
        uint32_t                id = 0;
        std::string             name;
        int                     session = -1;         // índice en sessions (-1 = ninguna)
        std::deque<NetMessage>  inbox;
    };
    struct Session {
        std::string name;
        int         maxPlayers = 7;
        bool        joinable = true;
        std::vector<uint32_t> members;
    };

    std::mutex            mutex;
    std::vector<Peer>     peers;
    std::vector<Session>  sessions;
    uint32_t              nextId = 1;
    uint32_t              services = kServiceTCP;    // servicios "disponibles" simulados

    Peer* find(uint32_t id) {
        for (auto& p : peers) if (p.id == id) return &p;
        return nullptr;
    }
};

class LoopbackTransport final : public NetTransport {
public:
    explicit LoopbackTransport(std::shared_ptr<LoopbackHub> hub) : hub_(std::move(hub)) {}

    bool initialize() override { initialized_ = true; return true; }
    void shutdown() override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        leaveLocked();
        initialized_ = false;
    }
    uint32_t services() const override { return hub_->services; }
    bool selectService(uint32_t kind) override { return (hub_->services & kind) != 0; }

    bool hostSession(const char* name, int maxPlayers) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        LoopbackHub::Session s;
        s.name = name ? name : "";
        s.maxPlayers = maxPlayers;
        hub_->sessions.push_back(s);
        session_ = int(hub_->sessions.size()) - 1;
        return true;
    }
    int findSessions(std::vector<std::string>& names) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        names.clear();
        for (auto& s : hub_->sessions) names.push_back(s.name);
        return int(names.size());
    }
    bool joinSession(int index) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        if (index < 0 || index >= int(hub_->sessions.size())) return false;
        auto& s = hub_->sessions[index];
        if (!s.joinable || int(s.members.size()) >= s.maxPlayers) return false;
        session_ = index;
        return true;
    }
    void disableJoin() override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        if (session_ >= 0) hub_->sessions[session_].joinable = false;
    }
    uint32_t createPlayer(const char* name) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        if (session_ < 0) return 0;
        LoopbackHub::Peer p;
        p.id = hub_->nextId++;
        p.name = name ? name : "";
        p.session = session_;
        hub_->peers.push_back(p);
        hub_->sessions[session_].members.push_back(p.id);
        local_ = p.id;
        return local_;
    }
    int findPlayers(std::vector<NetPeerInfo>& out) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        out.clear();
        if (session_ < 0) return 0;
        for (uint32_t id : hub_->sessions[session_].members)
            if (auto* p = hub_->find(id)) out.push_back({p->id, p->name});
        return int(out.size());
    }
    bool send(uint32_t toPeer, std::span<const uint8_t> data) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        auto* p = hub_->find(toPeer);
        if (!p || p->session != session_) return false;
        p->inbox.push_back(NetMessage{NetEvent::Data, local_, {data.begin(), data.end()}});
        return true;
    }
    bool broadcast(std::span<const uint8_t> data) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        if (session_ < 0) return false;
        for (uint32_t id : hub_->sessions[session_].members) {
            if (id == local_) continue;
            if (auto* p = hub_->find(id))
                p->inbox.push_back(NetMessage{NetEvent::Data, local_, {data.begin(), data.end()}});
        }
        return true;
    }
    bool poll(NetMessage& out) override {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        auto* p = hub_->find(local_);
        if (!p || p->inbox.empty()) return false;
        out = std::move(p->inbox.front());
        p->inbox.pop_front();
        return true;
    }
    uint32_t localPeer() const override { return local_; }

    // Simula la desconexión de este peer: los demás miembros reciben PlayerLeft.
    void disconnect() {
        std::lock_guard<std::mutex> lk(hub_->mutex);
        leaveLocked();
    }

private:
    void leaveLocked() {
        if (session_ < 0 || local_ == 0) return;
        auto& s = hub_->sessions[session_];
        for (uint32_t id : s.members) {
            if (id == local_) continue;
            if (auto* p = hub_->find(id)) p->inbox.push_back(NetMessage{NetEvent::PlayerLeft, local_, {}});
        }
        std::erase(s.members, local_);
        if (auto* me = hub_->find(local_)) me->session = -1;
        session_ = -1;
    }

    std::shared_ptr<LoopbackHub> hub_;
    int      session_ = -1;
    uint32_t local_ = 0;
    bool     initialized_ = false;
};

} // namespace dl2::net
