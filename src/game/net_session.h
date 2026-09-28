// net_session.h - Estado del módulo de red y capa de sesión (sustituye a CGNET.DLL: 0x457dbc-0x458640),
// recepción de cápsulas (NetReceiveCapsule 0x457f7c) y flujos de arranque anfitrión/cliente
// (FUN_00468a28 / FUN_00468898 / FUN_00468c94 / FUN_00468ea4 / GetNetGameOptions 0x470554).
#pragma once
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "game/game_state.h"
#include "game/net_protocol.h"
#include "game/net_transport.h"

namespace dl2::net {

constexpr int kMaxSessions = 20;    // DAT_0058389c: 20 nombres de 0x20 bytes

// Globales del original que sólo usa este módulo (los compartidos están en GameGlobals, ver globals.h).
struct NetState {
    NetTransport* transport = nullptr;      // sustituye a CGNET.DLL (lo instala la aplicación / el test)

    // --- capa CGNet (DAT_004d16f8..DAT_004d1718, DAT_00583854..DAT_00583b80) ---
    int      initialized = 0;               // DAT_004d1718 CGNet_Initialize hecho
    int      isHost = 0;                    // DAT_00583858 1 = anfitrión de la sesión (FUN_004582e0), 0 = cliente
    int      serviceKind = 0;               // DAT_00583854 servicio elegido (NetService)
    uint32_t sessionHandle = 0;             // DAT_004d1708
    uint32_t localPeer = 0;                 // DAT_004d170c handle de jugador local (CGNetSession_CreatePlayer)
    uint32_t hostPeer = 0;                  // DAT_004d1714 handle del anfitrión (cliente); FUN_0045860c / FUN_00458628
    int      localNetId = 0;                // DAT_004d16f8 (siempre 0; -> Player::netId)
    int      serviceCount = 0;              // DAT_00583b70
    bool     hasPending = false;            // DAT_004d1710 != 0: mensaje ya extraído pero no consumido
    NetMessage pending;                     // DAT_004d1710
    std::vector<std::string> sessionNames;  // DAT_0058389c[20][0x20] (+ handles DAT_00583b1c)
    char     sessionName[0x20] = {};        // DAT_0058385c

    // --- cápsulas / ACK ---
    uint32_t peerHandle[kMaxPlayers] = {};  // DAT_00653518[7] handle CGNet por índice de jugador
    NetCapsule lastDispatched;              // DAT_00653590 última cápsula despachada (+8 tipo, +0x16 jugador, +0x1a/+0x1c datos)
    NetCapsule lastAck;                     // DAT_00653534 última 0x42/0x43 recibida (+0x18 tipo, +0x1a resultado)
    int      ackState = 0;                  // DAT_004d826c 0 nada, 1 NACK, 2 ACK
    int      inHandler = 0;                 // DAT_004d8258 dentro de ProcessNetMessages
    int      suspendReceive = 0;            // DAT_004d8260 1 = no procesar cápsulas (bomba de mensajes anidada)
    int      applyingRemote = 0;            // DAT_004d8268 1 mientras se aplica un evento remoto (FUN_0045093c)
    int      flag3 = 0;                     // DAT_004d8298 (msg 3)
    int      newMasterFlag = 0;             // DAT_004d8294 (msg 0x35)
    int      inPlayerLeft = 0;              // DAT_006535f0 reentrada de NetPlayerLeft
    int      resetInProgress = 0;           // DAT_0065347c (ResetNetGame lo pone a 0)

    // --- WaitSync ---
    uint32_t waitSyncRandom = 0;            // DAT_0059f0f4 rand() del maestro al entrar en WaitSync
    int      waitSyncMismatch = 0;          // DAT_0059f0f8 algún esclavo envió otro rand -> Reseed
    int      resyncDialogUp = 0;            // DAT_004d5c24 diálogo "Re-synching Machines" abierto
    uint32_t syncWaitStart = 0;             // DAT_006520a4 timeGetTime() al empezar a esperar

    // --- transferencia de ficheros (NetGame.Sav / net_map.xfer) ---
    std::FILE* xferFile = nullptr;          // DAT_004dc310
    uint32_t xferTotal = 0;                 // DAT_006535f8 tamaño total
    uint32_t xferReceived = 0;              // DAT_006535fc bytes escritos
    int      xferBlocks = 0;                // DAT_006535f4 bloques enviados/recibidos
    int      xferFill = 0;                  // DAT_00653638 bytes acumulados del trozo comprimido actual
    uint8_t  xferRaw[0x410] = {};           // DAT_0065363c trozo descomprimido
    uint8_t  xferPacked[0x610] = {};        // DAT_00653a4c trozo comprimido (RLE)

    // --- resincronización (bloques de estado 0x45..0x48) ---
    int      stateBlockId = 0;              // DAT_00654800 bloque en recepción (0..6)
    uint32_t stateSize = 0;                 // DAT_006541e4 tamaño total del bloque
    int      stateFill = 0;                 // DAT_006541e8 bytes acumulados del trozo comprimido
    std::vector<uint8_t> stateBuf;          // DAT_004dc3c4 buffer del bloque (FUN_004418ec "NetStartState")
    uint32_t stateWritten = 0;              // DAT_006541ec - DAT_004dc3c4 (cursor de escritura)
    uint8_t  statePacked[0x610] = {};       // DAT_006541f0 trozo comprimido

    // --- ResetNetGame: orden de razas ---
    int      raceBefore[kMaxPlayers] = {};  // DAT_00653600 raza por índice antes de cargar (-1 = vacío)
    int      raceLoaded[kMaxPlayers] = {};  // DAT_0065361c raza por índice tras cargar
    uint32_t relationsSaved[kMaxPlayers][kMaxPlayers] = {};  // DAT_0065405c copia de Player::relations
    uint32_t relations2Saved[kMaxPlayers][kMaxPlayers] = {}; // DAT_00654120 copia de Player::relations2

    // --- CalculateGameCRC ---
    int      computingCrc = 0;              // DAT_004dc3c0 (SaveGame en curso para CHECKSUM.SAV)
};

extern NetState ns;

void ResetNetState();                       // pone ns a cero (ResetVariables / nueva partida)

// ----------------------------------------------------------------------------------------
// Capa de sesión (0x457dbc-0x458640): wrappers de CGNet sobre NetTransport
// ----------------------------------------------------------------------------------------
int      NetInit();                                   // orig: FUN_00457dbc  CGNet_Initialize + FindServices
uint32_t NetAvailableServices();                      // orig: FUN_00458138  máscara NetService
int      NetSelectService(uint32_t kind);             // orig: FUN_004581a8  DAT_00583854 = kind; elige el servicio
int      NetShutdown();                               // orig: FUN_00458298  CGNet_Cleanup
int      NetHostSession(const char* name);            // orig: FUN_004582e0  CreateSession + CreatePlayer("Deadlock 2 Host")
void     NetDisableJoin();                            // orig: FUN_00458384
int      NetSetClientMode();                          // orig: FUN_0045839c  isHost = 0
void     NetEnumSessions();                           // orig: FUN_004583ac  rellena ns.sessionNames (máx 20)
int      NetJoinSession(int index);                   // orig: FUN_00458434  Join + CreatePlayer("Deadlock 2 Player") + msg 9
int      NetConnectToAddress(const char* addr);       // orig: FUN_00458508
int      NetSendRaw(const NetCapsule& c, uint32_t toPeer, int forceBroadcast); // orig: FUN_00458550 (0 ok, -1 error)
int      NetLocalNetId();                             // orig: FUN_004585ec
int      NetBecomeHost();                             // orig: FUN_004585fc  isHost = 1
int      NetSetHostByPlayer(int player);              // orig: FUN_0045860c  hostPeer = peerHandle[player]
void     NetSetHostPeer(uint32_t peer);               // orig: FUN_00458628
int      NetFindHostPeer(uint32_t* out);              // orig: FUN_00458640  busca "Deadlock 2 Host" / "Closed Deadlock 2 Host"
int      NetPeekMessage();                            // orig: FUN_00457e14  0 = hay cápsula/aviso válido, 1 = nada
bool     NetPlayerDisconnect(uint32_t peer, NetCapsule& out); // orig: 0x457f00 fabrica un msg 0xd (Surrender)
bool     NetReceiveCapsule(NetCapsule& out);          // orig: 0x457f7c
int      NetTransportCheck();                         // orig: FUN_00458bc8  (3 = DirectPlay OK)

// ----------------------------------------------------------------------------------------
// Flujos de arranque (módulo startup 0x468000-0x470804, lógica sin UI)
// ----------------------------------------------------------------------------------------
int  HostGameSetup();                                  // orig: FUN_00468a28  crea sesión "Game 1", espera jugadores, SendSlaveInfo (0x43 ok / 0x35 volver)
int  WaitForPlayers();                                 // orig: FUN_00468898  1 = todos unidos, 2 = cancelado
int  JoinGame();                                       // orig: FUN_00468c94  0x43 ok / 0x38 reintentar / 0x35
int  NetLoadOrTransfer();                              // orig: FUN_00468ea4  envía/recibe la partida o el mapa al iniciar
int  GetNetGameOptions();                              // orig: 0x470554     lee deadlock.ini si gg.startupMode (1 = seguir, 0 = salir)
int  NetTcpStartup();                                  // orig: FUN_00468214  arranque directo por INI (TCP/IP)
int  NetSetupDialogBegin();                            // orig: FUN_00426868  parte lógica: comprueba el servicio y enumera sesiones

// Resultado de la lectura de [Startup] de deadlock.ini (FUN_004719a0, módulo scenario)
struct StartupIni {
    int  master = 0;          // "master"
    int  players = 0;         // "Players"
    char saveFile[0x80] = {}; // "Save File"
    char userName[0x20] = {}; // "User Name"
    char address[0x40] = {};  // "Master Address"
};

} // namespace dl2::net
