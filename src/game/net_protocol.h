// net_protocol.h - Protocolo lockstep de Deadlock II: cápsulas de 0x5c bytes, ids de mensaje, envío,
// ACK/NACK y despacho maestro/esclavo (0x474c00-0x479000 y 0x477e50-0x478fec del original).
//
// Modelo (ver docs/NETWORK.md):
//   - Un jugador es el MAESTRO (gg.hostPlayer == gg.localPlayer).  Los esclavos nunca modifican el
//     estado por su cuenta: envían una petición al maestro (FUN_004779c0 Broadcast), el maestro la aplica
//     con MasterDispatchNetMessage, responde ACK (0x42) / NACK (0x43) al peticionario y reenvía la
//     cápsula a todos los esclavos, que la aplican con SlaveDispatchNetMessage (FUN_004782ec).
//   - En partida local (gg.netGame == 0) Broadcast llama directamente a MasterDispatchNetMessage.
//   - La cápsula (NetCapsule) es un bloque de 0x5c bytes con layout fijo (ver kCapOff_*); los bytes no
//     usados eran basura de pila en el original y aquí van a cero.
#pragma once
#include <cstdint>
#include <cstring>
#include <span>

#include "game/game_state.h"

namespace dl2::net {

constexpr int kCapsuleSize = 0x5c;

// Offsets dentro de la cápsula (local_60 en FUN_004779c0 y hermanas)
constexpr int kCapOff_Session = 0x00;   // u8  DAT_004d5a54 (1 = sesión creada); el esclavo lo copia del msg 0xc
constexpr int kCapOff_Sender  = 0x01;   // u8  0xff = maestro, si no Player[local].netId (siempre 0 en v1.20)
constexpr int kCapOff_Route   = 0x02;   // u8  0xfe normal; 0xff = sólo lo acepta el anfitrión (msg 9 join); msg 0xc: ordinal del esclavo
constexpr int kCapOff_Handle  = 0x04;   // u32 handle CGNet del emisor (lo rellena NetReceiveCapsule; 0 al enviar)
constexpr int kCapOff_Type    = 0x08;   // u8  id de mensaje (NetMsg)
constexpr int kCapOff_Size    = 0x0e;   // u32 = 0x5c
constexpr int kCapOff_Player  = 0x16;   // i16 jugador (índice 0..6) al que se refiere / que lo envía
constexpr int kCapOff_D0      = 0x18;   // i16 Item   (FUN_00475048: "Item: %d")
constexpr int kCapOff_D1      = 0x1a;   // i16 Data1
constexpr int kCapOff_D2      = 0x1c;   // i16 Data2
constexpr int kCapOff_D3      = 0x1e;   // i16
constexpr int kCapOff_D4      = 0x20;   // i16
constexpr int kCapOff_Text    = 0x1a;   // char[59] + NUL en 0x55 (BroadcastText)
constexpr int kCapOff_Block   = 0x18;   // u8[0x40] (BroadcastBlock)
constexpr int kCapOff_Seed    = 0x1a;   // u32 (msg 0x4b Reseed; msg 0x33 = rand de WaitSync en D1/D2)
constexpr int kCapOff_Crc     = 0x1a;   // u32[7] (msg 0x44 SyncGame)
constexpr int kCapOff_Matrix  = 0x18;   // i8[7][7] (msg 0x55/0x56)
constexpr int kCapText_Max    = 0x3b;   // strncpy(.., 0x3b) + NUL en +0x55

#pragma pack(push, 1)
struct NetCapsule {
    uint8_t raw[kCapsuleSize] = {};

    uint8_t  u8(int off) const  { return raw[off]; }
    int16_t  i16(int off) const { int16_t v; std::memcpy(&v, raw + off, 2); return v; }
    uint16_t u16(int off) const { uint16_t v; std::memcpy(&v, raw + off, 2); return v; }
    uint32_t u32(int off) const { uint32_t v; std::memcpy(&v, raw + off, 4); return v; }
    void set8(int off, uint8_t v)   { raw[off] = v; }
    void set16(int off, int16_t v)  { std::memcpy(raw + off, &v, 2); }
    void set32(int off, uint32_t v) { std::memcpy(raw + off, &v, 4); }

    uint8_t  session() const { return raw[kCapOff_Session]; }
    uint8_t  sender() const  { return raw[kCapOff_Sender]; }
    uint8_t  route() const   { return raw[kCapOff_Route]; }
    uint32_t handle() const  { return u32(kCapOff_Handle); }
    uint8_t  type() const    { return raw[kCapOff_Type]; }
    uint32_t size() const    { return u32(kCapOff_Size); }
    int      player() const  { return i16(kCapOff_Player); }
    int16_t  d(int k) const  { return i16(kCapOff_D0 + 2 * k); }     // k = 0..4
    uint16_t ud(int k) const { return u16(kCapOff_D0 + 2 * k); }
    const char* text() const { return reinterpret_cast<const char*>(raw + kCapOff_Text); }
    const uint8_t* block() const { return raw + kCapOff_Block; }

    void setHandle(uint32_t h) { set32(kCapOff_Handle, h); }
    void setPlayer(int p)      { set16(kCapOff_Player, int16_t(p)); }
    void setD(int k, int16_t v){ set16(kCapOff_D0 + 2 * k, v); }
    void setText(const char* s);   // strncpy(0x3b) + NUL en 0x55 (FUN_004a6b48)
    void setBlock(const uint8_t* b64) { std::memcpy(raw + kCapOff_Block, b64, 0x40); }
};
#pragma pack(pop)
static_assert(sizeof(NetCapsule) == kCapsuleSize);

// Serialización explícita little-endian (byte a byte = layout del original en x86).
void encodeCapsule(const NetCapsule& c, uint8_t out[kCapsuleSize]);
bool decodeCapsule(std::span<const uint8_t> in, NetCapsule& out);   // false si el tamaño != 0x5c

// ----------------------------------------------------------------------------------------
// Ids de mensaje (byte +8).  Nombre = función manejadora del original cuando se conoce.
// ----------------------------------------------------------------------------------------
enum NetMsg : uint8_t {
    kMsgSessionDisconnected = 0x02, // FUN_004751d0 "Session #%d disconnected." (D1 = nº de sesión)
    kMsgFlag3               = 0x03, // FUN_00477fe0: DAT_004d8298 = 1 (maestro: ACK + reenvío)
    kMsgJoinRequest         = 0x09, // FUN_004770a0: alta de jugador (route 0xff; sólo anfitrión)
    kMsgSlaveInfo           = 0x0c, // FUN_004770fc: opciones de partida del maestro al esclavo (SendSlaveInfo)
    kMsgSurrender           = 0x0d, // FUN_00475150: el jugador abandona ("Master--Surrender")
    kMsgEvent               = 0x0e, // FUN_004755b4: FUN_0045093c(player, D0, D1, D2)
    kMsgEventText           = 0x0f, // FUN_00475660: FUN_0045093c(player, D0, -2, texto)
    kMsgEvent2              = 0x10, // FUN_00477684: FUN_0045093c(player, D0>>8, -1, D0&0xff, D1, D2)
    kMsgArmyStats           = 0x11, // FUN_00476e80: ejército D0, campo D1 (0 táctica,1 misión,2 retirada,3 job), valor D2
    kMsgArmyName            = 0x12, // FUN_00476ee4: ejército D0, nombre (texto)
    kMsgMoveUnit            = 0x13, // NetMoveUnit: ejército D0 -> territorio D1 (origen D2)
    kMsgDisbandUnit         = 0x14, // NetDisbandUnit: ejército D0
    kMsgStartConstruction   = 0x15, // NetStartConstruction: D0 = tipo<<8 | territorio, D1 = id (maestro), D2 = casilla
    kMsgDemolishBuilding    = 0x16, // NetDemolishBuilding: territorio D0, casilla D1, flag D2
    kMsgQueueUnit           = 0x17, // FUN_00475ed4: unidad D0 en territorio D1 (ACK D1 = resultado)
    kMsgDequeueUnit         = 0x18, // FUN_00476084: cola D0, índice D1, territorio D2
    kMsgBuildingTasks       = 0x19, // NetBuildingTasks: edificio D0, labor packed D1..D3, repeat D4
    kMsgBuildingFlags       = 0x1a, // NetBuildingFlags: edificio D0, flags D1, param10 D2
    kMsgPortTarget          = 0x1b, // FUN_004762fc: territorio D0, destino D1
    kMsgResetLaborToHousing = 0x1c, // FUN_00475d40: territorio D0
    kMsgReassignLabor       = 0x1e, // NetReassignLabor: territorio D0, de D1 a D2 (ids de edificio)
    kMsgReassignLaborByTask = 0x1f, // NetReassignLaborByTask: territorio D0, de D1 a D2, ranuras D3/D4
    kMsgMovePopulation      = 0x20, // FUN_0047636c: D0 = n&0x3fff | 0x4000 noNet, D1 origen, D2 destino, D3 casilla, D4 ranura
    kMsgAssignLaborHousing  = 0x21, // FUN_00475da4: territorio D0, edificio D1 (-1 = ninguno), D2 = n&0xff | 0x4000 | 0x8000
    kMsgSetResearch         = 0x22, // FUN_004764c0: tecnología D0
    kMsgSetTaxLevel         = 0x23, // FUN_00476518: nivel D0 (FUN_0045ea6c)
    kMsgSetTradeState       = 0x24, // FUN_00476588: territorio D0, estado D1 (FUN_0045ae38)
    kMsgTransferMaterials   = 0x27, // FUN_004765e8: D0 = origen<<8 | destino, D1 = material, D2 = cantidad
    kMsgOfferState          = 0x28, // FUN_004767c8: DAT_006534fc[D0] = D1
    kMsgTradeOffer          = 0x29, // FUN_0047681c: D0 material, D1 origen, D2 destino, D3 cantidad, D4 precio
    kMsgSellMaterial        = 0x2a, // FUN_004766e8: D0 = origen<<8 | destino, D1, D2 = c | b<<8 (FUN_00472448)
    kMsgBlackMarketTrade    = 0x2b, // FUN_00476c80: FUN_00436000(Player, D0, D1, D2)
    kMsgBlackMarketUnit     = 0x2c, // FUN_00476d08: FUN_00431e58(Player, D0, D1, id D2 (maestro))
    kMsgBlackMarketTech     = 0x2d, // FUN_00476d98: FUN_00431f6c(Player, D0)
    kMsgBlackMarketInfo     = 0x2e, // FUN_00476e0c: FUN_00435f5c(Player, D0)
    kMsgSelectLanding       = 0x30, // FUN_00477604: FUN_00427a0c(player, territorio D0)
    kMsgSelectRace          = 0x31, // FUN_00477660: raza D0, habilidad D1
    kMsgTurnDone            = 0x32, // FUN_00476fb8: turno D0
    kMsgWaitSyncReady       = 0x33, // FUN_004772d4 (maestro): turno D0, rand lo D1, hi D2
    kMsgWaitSyncResume      = 0x34, // FUN_0047731c (esclavo): turno D0
    kMsgNewMasterPeer       = 0x35, // FUN_0047800c: handle (+4) del nuevo maestro
    kMsgPlayerCountInc      = 0x36, // FUN_00478044: maestro: DAT_0058f200++
    kMsgAllTurnsDone        = 0x37, // FUN_00474e48: turnDone = 1 para todos
    kMsgUndoTurnDone        = 0x38, // FUN_00474fa0: turno D0
    kMsgFileStart           = 0x39, // FUN_0047997c: NetGame.Sav, tamaño = D1<<16 | D2
    kMsgFileBlock           = 0x3a, // FUN_00479a2c: 0x40 bytes comprimidos (RLE)
    kMsgFileDone            = 0x3b, // FUN_00479b38: ResetNetGame("NetGame.Sav")
    kMsgFileChunkEnd        = 0x3c, // FUN_00479a88: longitud descomprimida = D1<<8 | D2
    kMsgSetPlayerHuman      = 0x3d, // FUN_00479fd8: Player[D0].type = 1
    kMsgPactOffer           = 0x3e, // FUN_00476b8c: pacto D0 de D1 a D2
    kMsgMakePact            = 0x3f, // NetMakePact: pacto D0, jugadores D1/D2
    kMsgBreakPact           = 0x40, // NetBreakPact
    kMsgBreakPact2          = 0x41, // NetBreakPact_6a70
    kMsgAck                 = 0x42, // FUN_00474e84: D0 = tipo confirmado, D1 = resultado
    kMsgNack                = 0x43, // FUN_00474ea8: D0 = tipo rechazado
    kMsgSyncGame            = 0x44, // FUN_0047b4ac: turno D0, 7 x u32 CRC en +0x1a
    kMsgStateStart          = 0x45, // NetStartState: bloque D0, tamaño = D1<<16 | D2
    kMsgStateBlock          = 0x46, // FUN_0047c4c0: 0x40 bytes comprimidos
    kMsgStateChunkEnd       = 0x47, // FUN_0047c4f8: longitud descomprimida = D1<<8 | D2
    kMsgStateDone           = 0x48, // FUN_0047c53c: aplica el bloque
    kMsgCreateUnit          = 0x49, // FUN_004776e4: tipo D0, territorio D1, id D2 (maestro)
    kMsgCreateBuilding      = 0x4a, // FUN_00477838: tipo D0, territorio D1, id D2, casilla D3, id hab D4
    kMsgReseed              = 0x4b, // FUN_0047733c: semilla u32 en +0x1a
    kMsgPlayerName          = 0x4c, // FUN_00475228: nombre (texto) + handle
    kMsgLandingContinue     = 0x4d, // FUN_0047704c
    kMsgNop                 = 0x4e, // FUN_00475038
    kMsgRepeatFlags         = 0x4f, // FUN_00476214: territorio D0, Territory+0x9ae = D1
    kMsgMapFileStart        = 0x50, // FUN_00479de4: maps\net_map.xfer
    kMsgMapFileBlock        = 0x51, // FUN_00479eb0
    kMsgMapFileDone         = 0x52, // FUN_00479f90
    kMsgMapFileChunkEnd     = 0x53, // FUN_00479ee0
    kMsgAbortGame           = 0x54, // FUN_004752fc ("Master--AbortGame")
    kMsgAiMatrix1           = 0x55, // FUN_004753dc: DAT_005220a4 int[7][7] como bytes
    kMsgAiMatrix2           = 0x56, // FUN_0047543c: DAT_00522168 int[7][7] como bytes
};

struct NetMsgDesc {
    uint8_t     id;
    const char* name;      // nombre del manejador / mensaje
    const char* fields;    // campos de la cápsula
    const char* sender;    // quién lo envía (función del original)
    const char* handler;   // quién lo procesa
};
const NetMsgDesc* NetMsgDescribe(uint8_t id);          // nullptr si no está documentado
std::span<const NetMsgDesc> NetMsgTable();
const char* NetMsgName(uint8_t id);

// ----------------------------------------------------------------------------------------
// Envío (todas construyen la cápsula como el original y la entregan a NetSendCapsule)
// ----------------------------------------------------------------------------------------
void FillHeader(NetCapsule& c, uint8_t type);           // session/sender/route/size comunes (local_60..local_52)
void SendCapsule(const char* tag, NetCapsule& c, uint32_t toPeer);          // orig: FUN_00474cc4
void Broadcast(int player, uint8_t type, int16_t d0 = 0, int16_t d1 = 0, int16_t d2 = 0, int16_t d3 = 0, int16_t d4 = 0); // orig: FUN_004779c0
void BroadcastDirect(uint32_t toPeer, int player, uint8_t type, int16_t d0 = 0, int16_t d1 = 0, int16_t d2 = 0, int16_t d3 = 0, int16_t d4 = 0); // orig: 0x477b14
void SpecialBroadcast(int player, uint8_t type, int16_t d0 = 0, int16_t d1 = 0, int16_t d2 = 0, int16_t d3 = 0, int16_t d4 = 0); // orig: 0x477c00
void BroadcastText(int player, uint8_t type, int16_t d0, const char* text);  // orig: 0x477cf8
void BroadcastBlock(const uint8_t* block64, uint8_t type);                   // orig: 0x477e50
void BroadcastBlockDirect(uint32_t toPeer, const uint8_t* block64, uint8_t type); // orig: 0x477f04
void SendPlayerName(int player, const char* name);                           // orig: FUN_0047526c (msg 0x4c)
void SendAiMatrices();                                                       // orig: FUN_0047549c (msg 0x55/0x56)
void SendSlaveInfo();                                                        // orig: 0x4773e4 (msg 0xc a cada esclavo)
void BroadcastAbortGame();                                                   // orig: FUN_00475344 (msg 0x54)
void BroadcastTurnDone(int player);                                          // orig: FUN_00476ffc (msg 0x32)
void SendTurnDoneAll();                                                      // orig: FUN_0046e374 (turnDone de todas las IA)
void BroadcastLandingContinue();                                             // orig: FUN_00477070 (msg 0x4d)
void NetSetOfferState(int player, int state);                                // orig: FUN_004767f0 (msg 0x28)

// ACK / NACK y esperas cooperativas (hooks::pump)
int  WaitAck(uint8_t type);                 // orig: FUN_00474d0c  (0 nada, 1 NACK, 2 ACK) - sólo esclavos esperan
int  RequestAndWait(uint8_t type, int player); // orig: FUN_00474d90 (1 = aplicado, 0 = rechazado)
void AckMessage(NetCapsule& c);             // orig: FUN_00474ecc  (0x42)
void NackMessage(NetCapsule& c);            // orig: FUN_00474f14  (0x43)

// Despacho
void MasterDispatchNetMessage(NetCapsule& c, int fromLocal);   // orig: 0x4787c8
void SlaveDispatchNetMessage(NetCapsule& c);                   // orig: FUN_004782ec
void DispatchNetMessage(NetCapsule& c);                        // orig: FUN_00478fb8
int  ProcessNetMessages();                                     // orig: FUN_00477f9c (1 si procesó una cápsula)
void FlushNet();                                               // orig: FUN_00477e4c (vacía en v1.20)

// Peticiones de los clientes (lado "solicitante"; en local aplican directamente)
// (MoveUnit / DisbandUnit / SendUnitOrders / SetPlayerResearch / ProduceUnitInTerritory /
//  SetTerritoryPortTarget están declaradas en ai_api.h con esos nombres, en namespace dl2)
Building* RequestStartConstruction(Territory* t, int type, int site);                // orig: FUN_0047597c
void RequestDemolishBuilding(Territory* t, int site, int flag);                     // orig: FUN_00475a60
void RequestReassignLabor(Territory* t, Building* from, Building* to);              // orig: FUN_00475ba4
void RequestReassignLaborByTask(Territory* t, Building* from, int fromSlot, Building* to, int toSlot); // orig: FUN_00475ce8
void RequestResetLaborToHousing(Territory* t);                                      // orig: FUN_00475d60
void RequestAssignLaborFromHousing(Territory* t, int count, Building* b, int f1, int f2); // orig: FUN_00475e40
void RequestDequeueUnit(Territory* t, Player* p, int queueCat, int index);          // orig: FUN_004760d0
void RequestBuildingTasks(Territory* t, Building* b, const int32_t labor[5], uint8_t repeat); // orig: FUN_004761b0
void RequestBuildingFlags(Territory* t, Building* b);                               // orig: FUN_004762a8
void BroadcastRepeatFlags(Territory* t);                                            // orig: FUN_00476238
void RequestMovePopulation(Territory* from, Territory* to, int amount, int noNet, int16_t site, int16_t slot); // orig: FUN_00476448
void RequestSetTaxLevel(int player, int level);                                     // orig: FUN_0047654c
void RequestSetTradeState(int player, int territory, int state);                    // orig: FUN_004765a8
int  RequestTransferMaterials(Territory* from, Territory* to, const int32_t amounts[11]); // orig: FUN_00476668
void RequestSellMaterial(Territory* from, Territory* to, int a, int b, int c);      // orig: FUN_00476760
void RequestTradeOffer(Territory* from, Territory* to, int material, int amount, int price); // orig: FUN_0047691c
void RequestBlackMarketTrade(Player* p, int material, int amount, int territory);  // orig: FUN_00476cc0
void RequestBlackMarketUnit(Player* p, int unitIdx, int territory);                 // orig: FUN_00476d48
void RequestBlackMarketTech(Player* p, int tech);                                   // orig: FUN_00476dcc
void RequestBlackMarketInfo(Player* p, int info);                                   // orig: FUN_00476e40
void RequestPactOffer(int from, int to, int pact);                                  // orig: FUN_00476c44
void RequestMakePact(int p1, int p2, int pact);                                     // orig: FUN_00476b58
void RequestBreakPact(int p1, int p2, int pact);                                    // orig: FUN_00476aac
void RequestBreakPact2(int p1, int p2, int pact);                                   // orig: FUN_00476ae4
void RequestSelectLanding(int player, int territory);                               // orig: FUN_004775c8
void RequestSelectRace(int player, int race);                                       // orig: FUN_00477620
int  RequestUndoTurnDone(int player);                                               // orig: FUN_00474ff0
void SendEvent(int player, int a, int b, int c);                                    // orig: FUN_00475624 (msg 0xe)
void SendEventText(int player, int a, const char* text);                            // orig: FUN_004756c8 (msg 0xf)
void SendEvent2(int player, int hi, unsigned lo, int b, int c);                     // orig: FUN_004776b8 (msg 0x10)
Army*     RequestCreateUnit(Territory* t, int player, int unitType);                // orig: FUN_00477724 (msg 0x49)
Building* RequestCreateBuilding(Territory* t, int type, int site);                  // orig: FUN_00477888 (msg 0x4a)
void SurrenderPlayer(int player);                                                   // orig: FUN_00475198 (msg 0xd + PlayerSurrendered)

// Transferencia de ficheros (Load MultiPlayer Game / Load Map)
int  SendMultiplayerSaveFile();   // orig: FUN_00479700  gg.netSavePath -> msgs 0x39/0x3a/0x3c/0x3b + ResetNetGame
int  SendMapFile();               // orig: FUN_00479b6c  gg.scenarioPath -> msgs 0x50/0x51/0x53/0x52
int  RlePack(const uint8_t* src, uint8_t* dst, int n);          // orig: FUN_00479050 (PackBits)
void RleUnpack(const uint8_t* src, uint8_t* dst, unsigned n);   // orig: FUN_00478fec

// Utilidades
void NetErrorMessage(const char* text, const NetCapsule* c);   // orig: FUN_00475048 "%s\nPlayer: %d Item: %d Data1: %d Data2: %d"
int  CountHumanPlayers();                                       // orig: FUN_0045add0 (0 < type < 3, i < numPlayers)

} // namespace dl2::net
