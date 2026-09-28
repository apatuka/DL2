// game_state.h - Estructuras de datos del DEADLOCK.EXE original (Deadlock II: Shrine Wars v1.20)
//
// Reproducen BYTE A BYTE los layouts en memoria del ejecutable Borland C++ 5 (structs
// empaquetados, punteros de 32 bits).  Cada campo lleva la evidencia (función/cadena) que lo
// justifica; los bytes no identificados se llaman unk_<offset>.  Ver docs/SAVEFORMAT.md.
//
// Convenciones:
//   - Los punteros del original son de 32 bits: se representan con Ptr32<T> (uint32_t crudo).
//     En los ficheros de guardado se sustituyen por índices/IDs (ver SAVEFORMAT.md).
//   - Las direcciones (kAddr_*) son las de las variables globales en la sección DATA del EXE.
//   - "Building" = objeto de 0x122 bytes en DAT_005f0410 (FindBuildingByGlobalID, FUN_004750c4).
//     "Army"     = objeto de 0x5c bytes en DAT_00645370 (FindArmyByGlobalID, FUN_0047510c); el
//                  código original también lo llama "unit" (DeleteUnit, SyncCreateUnit).
//     "BuildingSite" = casilla de 52 bytes dentro de Territory (36 por territorio).
#pragma once
#include <cstddef>
#include <cstdint>

namespace dl2 {

template <class T>
struct Ptr32 {                 // puntero de 32 bits del binario original
    uint32_t raw = 0;
    explicit operator bool() const { return raw != 0; }
};
static_assert(sizeof(Ptr32<int>) == 4);

// ----------------------------------------------------------------------------------------
// Constantes globales (SaveGame FUN_00461488 / LoadGame FUN_004618e8 y lectores/escritores)
// ----------------------------------------------------------------------------------------
constexpr int      kMaxPlayers      = 7;      // Player[7] en DAT_0059f160
constexpr int      kMaxTerritories  = 112;    // memset(&DAT_005a43d0, 0, 0x4c040) = 112 * 0xadc
constexpr int      kMaxBuildings    = 1200;   // bucle 0x4b0 en FUN_00460258
constexpr int      kMaxArmies       = 560;    // bucle 0x230 en FUN_004605e0
constexpr int      kMaxEvents       = 50;     // DAT_00651cb4 .. DAT_0065209c (= contador)
constexpr int      kMapMaxSize      = 40;     // filas de 400 bytes = 40 tiles * 10
constexpr int      kNumTechs        = 48;     // bucle 0x30 en FUN_0045fe58
constexpr int      kNumSites        = 36;     // bucle 0x24 en FUN_00460870
constexpr int      kMaxTilesPerTerr = 48;     // Territory::tiles (0x80..0x140)
constexpr int      kJobsPerPlayer   = 50;     // bucle 0x32 en FUN_00460fa4
constexpr int      kNumMaterials    = 11;     // tabla PTR_s_Money (Money..Art)
constexpr int      kNumRaceStatRows = 64;     // 0x380 / 14
constexpr int      kNumRandomEvents = 25;     // bucle 0x19 en CreateRandomEvents
constexpr int      kSpiesPerPlayer  = 25;     // bucle 0x19 en FUN_0047d49c
constexpr uint32_t kSaveVersion     = 0x120;  // DAT_004d5ae8 (v1.20); ficheros GOG: 35..68
constexpr int      kHeaderGeneration = 4;     // DAT_004d1d3c: cabecera "version XXXXXXXXXXX"
constexpr int      kTerritoryUnsavedTail = 0x12a; // DAT_004d1cf8: cola transitoria no guardada

// Direcciones de los globales principales (sección DATA del EXE)
constexpr uint32_t kAddr_Players     = 0x0059f160;
constexpr uint32_t kAddr_Tiles       = 0x005a0550;
constexpr uint32_t kAddr_Territories = 0x005a43d0;
constexpr uint32_t kAddr_Buildings   = 0x005f0410;
constexpr uint32_t kAddr_Armies      = 0x00645370;
constexpr uint32_t kAddr_Events      = 0x00651cb4;
constexpr uint32_t kAddr_Jobs        = 0x00522584;
constexpr uint32_t kAddr_Techs       = 0x004fbbac;
constexpr uint32_t kAddr_RaceStats   = 0x00559e00;
constexpr uint32_t kAddr_MinisterJobs = 0x00522280;

// ----------------------------------------------------------------------------------------
// Enumeraciones demostradas por tablas de cadenas del EXE
// ----------------------------------------------------------------------------------------
enum class Race : int8_t {                 // tabla PTR_s_ChCh_t_00509038 (7 razas jugables)
    ChChT = 0, Cyth = 1, Human = 2, Maug = 3, ReLu = 4, Tarth = 5, UvaMosk = 6
    // Skirineen no es jugable (mercado negro); letras de fichero: C Y H M R T U (s_ChCht_005099cf)
};

enum class Terrain : uint8_t {             // tabla 0x00509054: "Sea","Plains","Forest","Swamp","Mountains","Wasteland"
    Sea = 0, Plains = 1, Forest = 2, Swamp = 3, Mountains = 4, Wasteland = 5
    // Territory::terrain == 0 => marítimo (Sea Shrine 0x2f); 5 (Wasteland) excluido de aterrizajes
};

enum class Material : uint8_t {            // tabla 0x0050906c "Money","Food","Energy","Wood","Iron","Steel",
    Money = 0, Food = 1, Energy = 2, Wood = 3, Iron = 4, Steel = 5, Endurium = 6, Triidium = 7,
    ElectronicParts = 8, AntiMatterPods = 9, Art = 10   // índice de Territory::materials[11]
};

enum class VictoryCondition : uint8_t {    // DumpGameOptions / INI "manifest_destiny|conquest|shrine_wars"
    ManifestDestiny = 0, Conquest = 1, ShrineWars = 2
};

enum class PlayerType : uint8_t {          // Player::type (FUN_0045add0 cuenta humanos: 0 < type < 3)
    None = 0, LocalHuman = 1, RemoteHuman = 2, AI = 3   // >= 3: IA (type-3 indexa PTR_FUN_004b5088)
};

enum class RacialAbilities : int32_t {     // INI "Racial Abilities" -> DAT_004d5b3c (FUN_00441128)
    Standard = 0, Best = 1, None = 2      // "standard_ability","best_ability","no_ability"
};

enum class BuildingType : uint8_t {        // tabla DAT_004f9dbc (paso 0x32, nombre en +0)
    NoBuilding = 0, Housing, ApartmentComplex, LuxuryHousing, CloningCenter, Farm, HydroponicFarm,
    FoodReplicator, SurfaceMine, MantleDrill, SubSpaceMagnet, NuclearPlant, FusionPlant,
    AntiMatterPlant, Factory, AutomatedFactory, ReplicationStation, Hospital, University, TechLab,
    CollectiveTechLab, CulturalCenter, Museum, ArtComplex, Shipyard, Hydroport, Airport,
    MilitaryAirbase, FuelDepot, LaserDefense, FlakLauncher, EnergyDefense, AntiMatterDefense,
    MissileBase, AntiColonyAssaultSilo, MilitaryTrainingCenter, Bunker, CityCenter /*0x25*/,
    SeaPlatform /*0x26*/, SeaHab /*0x27*/, TorpedoFort, KelpFarm, TidalEnergyPlant,
    TidalVortexGenerator, WeatherControlStation, NativeShrine /*0x2d*/, HiddenShrine /*0x2e*/,
    SeaShrine /*0x2f*/, Count /*48*/
};

enum class UnitType : uint8_t {            // tabla PTR_s_No_Unit_004faf7c (paso 0x24, nombre en +0)
    NoUnit = 0, LaserSquad, SAMTrooper, BattleTrooper, AssaultTrooper, LaserCannon, FusionCannon,
    DisruptorCannon, HolocaustCannon, TurboWingFighter, StarflareBomber, SupernovaSpyjet,
    SeaTransport, ShockwaveDreadnought, ShockwaveCarrier, CommandCorps, ScatterpackWarhead,
    GroundbreakerWarhead, SupernovaWarhead, LaserDefense, FlakLauncher, EnergyDefense,
    AntiMatterDefense, Militia, Scout, Colonizer /*0x19*/, Medic, AAV, AirCommand, Destroyer,
    AttackSubmarine, SeaColonizer, TorpedoFort, SeaCommand, FlakShip, SiegeCruiser, SiegeMissile,
    LandMine, SeaMine, Count /*39*/
};

enum class TechId : uint8_t {              // tabla DAT_004fbbac (paso 0x32, nombre en +0x14)
    Nothing = 0, AdvancedMedicine, Metallurgy, NuclearFusion, Electronics, ShockwaveProjector, Flak,
    FusionCannon, Automation, Cloning, SurfaceToAirMissiles, SyntheticFertilizer, NeutrionicFuel,
    Hoverway, ChaosComputers, Rocketry, MolecularBonding, ZeroFrictionHulls, UnderwaterTracking,
    AdvancedStructures, EnduriumMining, StarflareBombs, AntiMatterContainment, TargettingComputers,
    ProximityDetectors, EnergyDeflectors, IonWeapons, PowerCells, AntiMatterRifles,
    TriidiumProcessing, CortexScanner, OrbitalSurveillance, PsiHelmet, NativeLanguages,
    VortexEmitters, FoodReplication, DisruptorBeams, AntiMatterDeflectors, MetalReplication,
    Cloaking, AssaultArmor, SubSpaceScanner, MesotronicGenerators, AdvancedCloaking,
    AntiMatterBeams, Uncloaking, Transporters, TimeDilation, Count /*48*/
};

enum class BuildingTask : uint8_t {        // tabla 0x00509180 (tareas de edificio, Building::task[])
    Construction = 0, MineIron, MineEndurium, Research, ElectronicParts, Culture, CreateArt,
    IronToSteel, EnduriumToTriidium, BuildUnits, Food, Wood, Trade, Energy, AntiMatterPods, Clone,
    TrainUnits, HealMilitia, HousePopulace, Upgrade
};

enum class Minister : uint8_t {            // tabla PTR_s_DEFENSE_MIN_004b5fd0 ("Run By" en FUN_0041bfc0)
    Defense = 0, War = 1, Government = 2, Economic = 3, Tech = 4, Labor = 5
};

enum class MinisterJobType : uint8_t {     // tabla PTR_s_NULL_JOB_004b5fe8 (DebugJobsDialog FUN_00405d54)
    NullJob = 0, HeadJob, CreateBldg, BuildBldg, FillTaskforce, CreateUnit, BuildUnit, LearnTech,
    GetMaterial, MaintainMorale, GrowPopulation, HealPlague, Stockpile, MaintainUnit
};

enum class TaskForceGoal : int32_t {       // tabla PTR_s_NO_TF_GOAL_004b6bd4 (Job::goal)
    NoTFGoal = 0, Reserve, LandExpand, LandAttack, LandHunt, LandDefend, LandSpy, LandMine,
    LandShrine, TransportUnits, SeaExpand, SeaAttack, SeaHunt, SeaDefend, SeaSpy, SeaMine,
    SeaShrine, SeaBesiege, AirAttack, AmphibAttack, Special
};

enum class TaskForceStatus : int32_t {     // tabla PTR_s_NEED_SPACE_004b6c7c (Job::status)
    NeedSpace = 0, NeedFood, NeedWood, NeedIron, NeedEnergy, NeedEndurium
};

#pragma pack(push, 1)

// ----------------------------------------------------------------------------------------
// 1. Cabecera del fichero (FUN_00461f74 escribe, FUN_00461ff4 lee) - 0x9c bytes
// ----------------------------------------------------------------------------------------
struct SaveHeader {
    char     text[88];      // "Deadlock 2  (c)1997 Accolade Inc.  All Rights Reserved.\nPre-release version XXXXXXXXXXX"
    uint32_t version;       // DAT_004d5ae8 al guardar (0x120); al cargar -> DAT_00583da8 (rechazado si > 0x120)
    int32_t  isMap;         // 1 = fichero de mapa del editor (sólo cabecera+mundo+territorios reducidos+tiles)
    int32_t  zero;          // siempre 0
    int32_t  minusOne;      // siempre -1
    uint8_t  pad[52];       // memset 0 de los primeros 20 bytes; el resto basura de pila
};
static_assert(sizeof(SaveHeader) == 0x9c);

// ----------------------------------------------------------------------------------------
// 2. Opciones de partida (FUN_0045f664 escribe / FUN_0045f828 + FUN_00462100 leen) - 0xac
//    Los offsets coinciden con los que usa el parser de "Scenario Options" (FUN_00471170).
// ----------------------------------------------------------------------------------------
struct GameOptions {
    int32_t  turn;              // 0x00 DAT_0059f154  turno actual ("Turn %3d" en DEBUG.TXT)
    uint32_t gameSeed;          // 0x04 DAT_0059f158  ResetVariables: FUN_0046c9cc("GameSeed")
    int32_t  gameId;            // 0x08 DAT_0059f15c  SaveGame: FUN_0046c9d8(10000,"SaveGame"); FUN_00477394 lo usa como semilla (srand / msg de red 0x4b)
    int32_t  numPlayers;        // 0x0c DAT_004d5aec  INI "Players" (2..7)
    int32_t  winCities;         // 0x10 DAT_004d5af0  INI "Win Cities" {2,3,5,7,10} (Manifest Destiny)
    int32_t  winShrines;        // 0x14 DAT_004d5af8  INI "Win Shrines" (Shrine Wars: "%d for %d turns")
    int32_t  winTurns;          // 0x18 DAT_004d5afc  INI "Win Turns"
    uint8_t  victory;           // 0x1c DAT_004d5b00  VictoryCondition (2 = Shrine Wars)
    uint8_t  pad_1d;            // 0x1d relleno (memset 0)
    int32_t  fastProduction;    // 0x1e DAT_004d5b08  INI "Fast Production" ("Fast Prod" en DEBUG.TXT)
    int32_t  randomEvents;      // 0x22 DAT_004d5b04  INI "Random Events" (CreateRandomEvents lo comprueba)
    int32_t  aiSkill;           // 0x26 DAT_004d5b0c  INI "AI Skill Level" (0..4; diálogo ids 0x17..0x1b)
    uint8_t  reserved_2a[16];   // 0x2a memset 0 (formato antiguo: 8 x u16 contadores de id por jugador)
    uint32_t netFlags;          // 0x3a DAT_004d5b24  bit0 alternado en FUN_0047d2f0 (sincronía de red)
    int32_t  localPlayer;       // 0x3e DAT_0058f1f4  índice del jugador local (sólo se restaura si param_2)
    int32_t  eventLogFirst;     // 0x42 DAT_00651cb0  primer evento visible del Event Log (FUN_00403310)
    int32_t  eventCount;        // 0x46 DAT_0065209c  nº de entradas del Event Log guardadas (<= 50)
    int32_t  autoTimer;         // 0x4a DAT_004d5b2c  INI "Auto Timer" (temporizador de turno activo)
    int32_t  reserved_4e;       // 0x4e DAT_004d5b28  sólo save/load (valor observado 0x7f)
    int32_t  autoTimerClock;    // 0x52 DAT_004d5b30  INI "Auto Timer Clock" segundos (3..960, def. 300)
    int32_t  lastPlayerTimer;   // 0x56 DAT_004d5b34  INI "Last Player Timer" (excluyente con autoTimer)
    int32_t  lastPlayerClock;   // 0x5a DAT_004d5b38  INI "Last Player Clock" segundos (3..960)
    int32_t  racialAbilities;   // 0x5e DAT_004d5b3c  INI "Racial Abilities" (RacialAbilities; FUN_00441128)
    uint8_t  reserved_62[4];    // 0x62 memset 0
    uint16_t hasWon[7];         // 0x66 DAT_0065e42c  por jugador, =1 cuando cumple la condición de victoria (FUN_00486e34)
    int32_t  worldResources;    // 0x74 DAT_004d5a90  INI "World Resources" (FUN_004669d8)
    int32_t  nextGlobalId;      // 0x78 DAT_004d825c  contador de IDs globales (FUN_00474cfc: ++ y trunca a u16)
    int32_t  campaign;          // 0x7c DAT_004d5a94  índice de campaña (0 = ninguna; tabla DAT_004c61e0 paso 0xd8)
    uint8_t  playerSkill[7];    // 0x80 DAT_005a0548  "Player Name (Skill Level)" por jugador (0..4, def. 2)
    uint8_t  playersMask;       // 0x87 DAT_0059f0fc  máscara de jugadores presentes (bit i = Player[i].type > 0)
    int32_t  shrineTurns[7];    // 0x88 DAT_0065e404  turnos consecutivos cumpliendo Shrine Wars (FUN_00486e34)
    uint8_t  campaignBytes[3];  // 0xa4 3 bytes de la tabla de campaña (DAT_004c61e0+camp*0xd8+k*0x44)
    uint8_t  pad_a7;            // 0xa7
    int32_t  allowAlliances;    // 0xa8 DAT_004d5af4  INI "Allow Alliances" ("Alliances On" en DEBUG.TXT)
};
static_assert(sizeof(GameOptions) == 0xac);
static_assert(offsetof(GameOptions, autoTimer) == 0x4a);
static_assert(offsetof(GameOptions, hasWon) == 0x66);
static_assert(offsetof(GameOptions, allowAlliances) == 0xa8);

// ----------------------------------------------------------------------------------------
// 3. Parámetros del mundo (DAT_004d5b10..DAT_004d5b23; FUN_0045fa10 / FUN_0045fa34) - 0x14
// ----------------------------------------------------------------------------------------
struct WorldParams {
    uint32_t seed1;             // 0x00 DAT_004d5b10  ResetVariables: FUN_004ae5b0() (rand)
    uint32_t rngSeed;           // 0x04 DAT_004d5b14  LoadGame: FUN_004ae594(DAT_004d5b14) (srand)
    uint16_t numTerritories;    // 0x08 DAT_004d5b18  nº de territorios (índices 1..N; máx 111)
    uint8_t  width;             // 0x0a DAT_004d5b1a  ancho del mapa en tiles ("World W.")
    uint8_t  height;            // 0x0b DAT_004d5b1b  alto del mapa ("World H.")
    uint8_t  worldType;         // 0x0c DAT_004d5b1c  tipo de mundo/clima 0..5 (FUN_004684d0: rand%6)
    uint8_t  terrainPct[6];     // 0x0d DAT_004d5b1d  % de Sea,Plains,Forest,Swamp,Mountains,Wasteland (suma 100)
    uint8_t  numColonySites;    // 0x13 DAT_004d5b23  = tamaño*2+12 (FUN_004684d0)
};
static_assert(sizeof(WorldParams) == 0x14);

// ----------------------------------------------------------------------------------------
// 4. Jugador (DAT_0059f160, 7 x 0x2d8)
// ----------------------------------------------------------------------------------------
struct AiMinister {              // 6 por jugador, inicializados en FUN_00401830 (IA)
    uint8_t  index;              // 0x00 0..5
    uint8_t  unk_01;
    uint32_t fn[4];              // 0x02 punteros a función (FUN_00401988 por defecto) - no válidos tras cargar
    uint8_t  unk_12[0x48];       // 0x12
};
static_assert(sizeof(AiMinister) == 0x5a);

struct Player {
    uint8_t  index;              // 0x000 índice propio (FUN_00474718: Player[i]+0 = i)
    uint8_t  type;               // 0x001 PlayerType (0 none, 1 local, 2 remoto, >=3 IA; 0x7f en FUN_0042d660)
    int8_t   race;               // 0x002 Race (PTR_s_ChCh_t_00509038[race])
    uint8_t  unk_03;
    uint16_t netId;              // 0x004 id de red (BroadcastDirect/BroadcastText lo envían)
    int16_t  homeTerritory;      // 0x006 territorio de aterrizaje (FUN_0046d2e8: = Territory::index)
    uint8_t  turnDone;           // 0x008 turno terminado (SyncBeginTurn, RunAITurns: ==0 pendiente)
    uint8_t  foodFlags;          // 0x009 bits 0/1/2 hambruna (ConsumeFood, FUN_0046b818)
    uint8_t  scandals;           // 0x00a contador de escándalos de espionaje (FUN_0047d49c, máx 11)
    int8_t   taxLevel;           // 0x00b nivel de impuestos, índice en DAT_004d57ec (def. 2)
    int32_t  credits;            // 0x00c créditos ("%d Cr." en FUN_00432fc0; 500 iniciales)
    uint8_t  unk_10[0x28];       // 0x010
    uint8_t  unk_38;             // 0x038 = 0x7f al crear (FUN_00474718)
    uint8_t  unk_39;
    Ptr32<void> localList;       // 0x03a lista enlazada {u32 val; next} sólo del jugador local (FUN_0045fa4c)
    int8_t   currentResearch;    // 0x03e TechId en investigación (0 = ninguna; FUN_0046ac44, FUN_0040cea4)
    uint8_t  unk_3f;
    int16_t  lastIncome;         // 0x040 FUN_0046ac44: = stats.income (si !DAT_004d5804)
    uint8_t  unk_42[4];
    uint32_t aiVtbl[4];          // 0x046 4 punteros de PTR_DAT_004b502c[type*6] (personalidad IA)
    uint32_t aiParam1;           // 0x056 DAT_004b503c[type*0x18]
    uint32_t aiParam2;           // 0x05a DAT_004b5040[type*0x18]
    AiMinister ministers[6];     // 0x05e 6 x 0x5a = 0x21c (memset 0 en FUN_00401830)
    uint32_t relations[7];       // 0x27a máscaras de pactos con cada jugador (FUN_004412d4: bit 0x10 = ?, 0x1e = pactos)
    uint32_t relations2[7];      // 0x296 segunda máscara (FUN_004415d0 borra ambas)
    uint8_t  unk_2b2;
    char     name[33];           // 0x2b3 nombre ("New Player" / nombre de IA PTR_s_Sting_00509938[race])
    int32_t  defeated;           // 0x2d4 != 0 => eliminado (CalculatePlayersScores pone score 0); se limpia en campaña
};
static_assert(sizeof(Player) == 0x2d8);
static_assert(offsetof(Player, localList) == 0x3a);
static_assert(offsetof(Player, ministers) == 0x5e);
static_assert(offsetof(Player, relations) == 0x27a);
static_assert(offsetof(Player, name) == 0x2b3);

// ----------------------------------------------------------------------------------------
// 5. Tile del mapa (DAT_005a0550, filas de 400 bytes = 40 x 10; se guardan h x w)
// ----------------------------------------------------------------------------------------
struct Tile {
    uint8_t  x;                  // 0x00 columna (FUN_00466128 / FUN_00462624)
    uint8_t  y;                  // 0x01 fila
    int16_t  territory;          // 0x02 índice de territorio (FUN_00466128 calcula numTerritories = max+1)
    uint8_t  borderFlags;        // 0x04 bits de frontera con otros territorios (FUN_0046237c)
    uint8_t  terrain;            // 0x05 tipo gráfico de terreno 0..6 (tabla DAT_004d553c paso 0x20)
    uint8_t  overlay;            // 0x06 sprite superpuesto (0 = ninguno; FUN_00440b68)
    uint8_t  unk_07;
    int16_t  pathCost;           // 0x08 coste de ruta temporal (0x7fff = no alcanzado; FUN_0047da24)
};
static_assert(sizeof(Tile) == 10);
constexpr int kTileRowBytes = 400;

// ----------------------------------------------------------------------------------------
// 6. Casilla de construcción dentro del territorio (36 x 0x34 en Territory+0x142)
// ----------------------------------------------------------------------------------------
struct BuildingSite {            // Territory+0x140 + i*0x34 (FUN_0044e600 lee T+0x142+i*0x34, FUN_00405d54 T+0x154+i*0x34)
    uint16_t unk_00;             // 0x00 (0 en todos los ficheros)
    uint16_t terrainFlags;       // 0x02 bits 0-3 = terreno de la casilla (FUN_0044e600), bits 8-11 (0x200 = elevada; DrawSTileBuilding)
    uint8_t  value;              // 0x04 guardado en modo mapa (FUN_00460d84)
    uint8_t  unk_05[0x0f];       // 0x05
    Ptr32<struct Building> building; // 0x14 edificio construido (save: ID global; load: FindBuildingByGlobalID)
    uint8_t  unk_18[0x1c];       // 0x18
};
static_assert(sizeof(BuildingSite) == 0x34);
static_assert(offsetof(BuildingSite, building) == 0x14);

// ----------------------------------------------------------------------------------------
// 7. Territorio (DAT_005a43d0, 112 x 0xadc; se guardan índices 1..N, 0x9b2 bytes cada uno)
// ----------------------------------------------------------------------------------------
struct QueueRecord {             // nodo de las 5 colas de producción (FUN_00484da8 asigna 0x34)
    uint8_t  unitType;           // 0x00 UnitType (FUN_00484ee0)
    uint8_t  unk_01;
    uint16_t count;              // 0x02 cantidad pendiente (FUN_00484f10; ProduceUnits decrementa)
    int32_t  data[11];           // 0x04 materiales/progreso (FUN_00484f48 copia 11 dwords)
    Ptr32<QueueRecord> next;     // 0x30 (no se guarda: en fichero van 0x30 bytes por nodo)
};
static_assert(sizeof(QueueRecord) == 0x34);
constexpr int kQueueRecordSaved = 0x30;

struct QueueHead {               // objeto de 8 bytes en heap (FUN_00460a74: malloc(8) + FUN_00484c2c {0,0})
    Ptr32<QueueRecord> first;    // 0x00
    Ptr32<QueueRecord> cursor;   // 0x04 iterador (FUN_00484ea4/FUN_00484ebc)
};
static_assert(sizeof(QueueHead) == 8);

struct Territory {
    char     name[25];           // 0x000 nombre ("%s Landing", "Morale in %s"); 24 chars + NUL
    uint8_t  unk_19;
    uint16_t index;              // 0x01a índice propio (Army/Job guardan punteros como este índice)
    uint32_t flags;              // 0x01c bit0 = capital local, bit1..: &3 (FUN_00440b68), 0x10 = shrine colocado,
                                 //       0x100 = sin tiles, bit 8 de +0x1d (&1) = inválido/agua; load: &= 0xfff0
    int8_t   owner;              // 0x020 jugador propietario (-1 = ninguno)
    uint8_t  terrain;            // 0x021 Terrain (0 = mar; guardado también en modo mapa)
    int8_t   continent;          // 0x022 id de continente 0..31 (FUN_004423b4; tabla DAT_0055a820)
    uint8_t  unk_23[3];
    int8_t   tradeState;         // 0x026 -1/0/1 (FUN_00436ef4, mercado)
    int8_t   morale;             // 0x027 moral 0..100 ("Morale in %s", escándalos la reducen)
    uint8_t  unk_28[2];
    int16_t  taxAdjust;          // 0x02a "Local Tax Adjustment" (FUN_00436a44; FUN_0046ab18 suma)
    int16_t  unk_2c;
    int16_t  tradeIncome;        // 0x02e FUN_0046ab18: stats[4] += *(s16*)(T+0x2e)
    int16_t  population;         // 0x030 población ("Population %d/%d"; "Territories must have population")
    int16_t  unk_32;
    uint8_t  unk_34;
    uint8_t  knowledge;          // 0x035 =100 al colonizar / en editor (FUN_0047c730, FUN_00460870)
    int16_t  unk_36;
    int16_t  knownPopulation;    // 0x038 última población conocida (FUN_0047fc84 si visibility != 4)
    int32_t  materials[11];      // 0x03a almacén por Material (Money..Art); FUN_00432fc0 muestra [1..10]
    uint8_t  visibility[7];      // 0x066 nivel de conocimiento por jugador (>2 visible, 4 = propio)
    uint8_t  unk_6d[7];          // 0x06d por jugador (valores 9/12 observados)
    int8_t   centerTile;         // 0x074 índice en tiles[] del tile central (FUN_00449870, -1 si no)
    int8_t   secondTile;         // 0x075 índice en tiles[] secundario (FUN_0045bf78)
    Ptr32<struct Army> armies;   // 0x076 lista de ejércitos propios (Army::next); save: ID global
    Ptr32<struct Army> foreignArmies; // 0x07a lista de ejércitos ajenos (ReLinkArmy); save: ID global
    uint8_t  numTiles;           // 0x07e nº de tiles del territorio (FUN_00462624)
    uint8_t  unk_7f;
    Ptr32<Tile> tiles[48];       // 0x080 punteros a Tile; save: (x | y<<16); load: &Tiles + y*400 + x*10
    BuildingSite sites[36];      // 0x140 36 casillas de 0x34 (terreno en +0x142, edificio en +0x154)
    uint16_t adjacency[7];       // 0x890 máscara de 112 bits de territorios adyacentes (FUN_0044da3c)
    uint8_t  unk_89e;
    uint8_t  freeSites;          // 0x89f nº de casillas libres (FUN_004669d8)
    uint32_t adjContinents;      // 0x8a0 máscara de continentes adyacentes (FUN_004423b4)
    uint32_t unk_8a4;            // 0x8a4 máscara (FUN_00402fe8)
    uint32_t exploredMask;       // 0x8a8 máscara de jugadores que lo han explorado (FUN_0045bf78)
    uint32_t coastal;            // 0x8ac 0/1 acceso al mar (FUN_004669d8, FUN_00466508)
    uint8_t  unk_8b0[0xea];      // 0x8b0
    Ptr32<QueueHead> queues[5];  // 0x99a punteros a 5 colas de producción en heap (save: crudos; luego u8 n + n*0x30 por cola)
    uint8_t  hoverway;           // 0x9ae nivel de carretera/hoverway (FUN_0044c3fc, FUN_00476214); 0 en formato antiguo
    uint8_t  unk_9af;
    uint16_t portTarget;         // 0x9b0 territorio destino de puerto (FUN_0044da3c en formato antiguo)
    // ---- a partir de aquí NO se guarda (0xadc - 0x12a = 0x9b2) ----
    uint16_t colonyFlag;         // 0x9b2 =0 al colonizar (FUN_0046d2e8, FUN_0047c730)
    uint8_t  unk_9b4[0xca];      // 0x9b4 datos de IA (FUN_00442f68, FUN_0040d4a8)
    int32_t  production[11];     // 0xa7e producción por turno por Material (FUN_0046ab18 memset 0x2c)
    int32_t  consumption[11];    // 0xaaa consumo por turno (FUN_0046ab18)
    uint8_t  unk_ad6[6];         // 0xad6
};
static_assert(sizeof(Territory) == 0xadc);
static_assert(offsetof(Territory, index) == 0x1a);
static_assert(offsetof(Territory, materials) == 0x3a);
static_assert(offsetof(Territory, armies) == 0x76);
static_assert(offsetof(Territory, tiles) == 0x80);
static_assert(offsetof(Territory, sites) == 0x140);
static_assert(offsetof(Territory, adjacency) == 0x890);
static_assert(offsetof(Territory, queues) == 0x99a);
static_assert(offsetof(Territory, colonyFlag) == 0xadc - kTerritoryUnsavedTail);
static_assert(offsetof(Territory, production) == 0xa7e);
constexpr int kTerritorySavedBytes = 0xadc - kTerritoryUnsavedTail;   // 0x9b2

// ----------------------------------------------------------------------------------------
// 8. Edificio (DAT_005f0410, 1200 x 0x122; FUN_0044d890 inicializa)
// ----------------------------------------------------------------------------------------
struct Building {
    uint16_t id;                 // 0x000 ID global (FindBuildingByGlobalID busca aquí; 0x3ff usado en nombres)
    uint16_t flags;              // 0x002 bit1 = construido (FUN_0046b0e4), bit2 = activo (FUN_0044f110),
                                 //       bit5 = obra ("Construction Site"), bits 8..12 = tareas (GetBuildingTasks)
    uint8_t  type;               // 0x004 BuildingType (0 = libre; 0x25 City Center, 0x26 Sea Platform)
    uint8_t  category;           // 0x005 = BuildingTypeDef+7 (0x11 vivienda, 0x0b shrine, ...)
    uint8_t  race;               // 0x006 raza del dueño para viviendas/hub (FUN_0044d890)
    int8_t   site;               // 0x007 índice de BuildingSite 0..35 (FUN_0044e600)
    int16_t  territory;          // 0x008 índice del territorio ("Location: %s / %d")
    int16_t  unk_0a;             // 0x00a = 0 al crear
    int16_t  hubLevel;           // 0x00c sólo City Center: FUN_0044de48(owner)-1
    int8_t   minister;           // 0x00e Minister que lo dirige ("Run By" en FUN_0041bfc0)
    uint8_t  unk_0f;
    int16_t  unk_10;             // 0x010 = 0
    int16_t  unk_12;             // 0x012 = 0
    int16_t  turnsLeft;          // 0x014 turnos de construcción restantes (0 = terminado; GetBuildingTasks)
    int16_t  unk_16;             // 0x016 = 0
    int32_t  labor[5];           // 0x018 trabajadores por ranura ("Labor Assigned %d/%d" suma las 5)
    uint8_t  task[5];            // 0x02c BuildingTask por ranura (0 = principal; GetBuildingTasks)
    uint8_t  unk_31[4];          // 0x031
    uint8_t  unk_35;
    uint8_t  unk_36[8];          // 0x036
    int32_t  cost[11];           // 0x03e materiales pendientes de pagar (FUN_0044f110/FUN_004720f4, memset 0x2c)
    int32_t  taskData[4][11];    // 0x06a por tarea 1..4 x Material (memset 0xb0: 0x6a..0x11a)
    Ptr32<Building> prev;        // 0x11a anterior en la lista de activos (FUN_0044cabc); save: ID
    Ptr32<Building> next;        // 0x11e siguiente en la lista (save: ID; load: FindBuildingByGlobalID)
};
static_assert(sizeof(Building) == 0x122);
static_assert(offsetof(Building, cost) == 0x3e);
static_assert(offsetof(Building, taskData) == 0x6a);
static_assert(offsetof(Building, prev) == 0x11a);

// ----------------------------------------------------------------------------------------
// 9. Ejército/unidad (DAT_00645370, 560 x 0x5c; FUN_00445d30 inicializa)
// ----------------------------------------------------------------------------------------
struct Army {
    uint16_t id;                 // 0x00 ID global (FindArmyByGlobalID); nombre usa id & 0x3ff
    uint16_t unk_02;             // 0x02 = 0 al crear
    uint16_t unk_04;
    uint8_t  type;               // 0x06 UnitType (0 = libre; DeleteUnit: 0x13/0x04 portan carga)
    uint8_t  unitClass;          // 0x07 = UnitTypeDef+0x0b (clase: 3 = ?, 0x0d = ?; DeleteUnit)
    int8_t   owner;              // 0x08 jugador
    uint8_t  unk_09;
    uint8_t  strength;           // 0x0a FUN_00447190(army) al crear
    char     name[24];           // 0x0b "%s %s #%d" (raza, tipo, id&0x3ff); FUN_004a6b48(...,0x18)
    uint8_t  unk_23;
    uint8_t  moves;              // 0x24 puntos de movimiento (0x1a para clases 4,6,0xb,0xd,0x11)
    uint8_t  unk_25;             // 0x25 = 0
    uint8_t  health;             // 0x26 salud % (100 al crear)
    uint8_t  unk_27;
    int16_t  experience;         // 0x28 veteranía (200 para unidades de campaña; FUN_00447a40)
    int16_t  unk_2a;             // 0x2a = 0
    int16_t  unk_2c;
    uint8_t  unk_2e[8];
    int16_t  job;                // 0x36 índice+1 del Job (task force) al que pertenece (FUN_00461078)
    Ptr32<Territory> territory;  // 0x38 territorio actual; save: Territory::index
    Ptr32<Territory> dest;       // 0x3c destino (Task Force "%s, %s, %s"); save: índice
    Ptr32<Territory> origin;     // 0x40 origen; save: índice
    Ptr32<void> unk_44;          // 0x44 transitorio (load lo pone a 0)
    Ptr32<Army> cargo[3];        // 0x48 unidades transportadas / enlace transporte<->carga; save: ID
    Ptr32<Army> next;            // 0x54 siguiente en la lista del territorio (o lista libre); save: ID
    Ptr32<Army> prev;            // 0x58 anterior; save: ID
};
static_assert(sizeof(Army) == 0x5c);
static_assert(offsetof(Army, name) == 0xb);
static_assert(offsetof(Army, territory) == 0x38);
static_assert(offsetof(Army, cargo) == 0x48);

// ----------------------------------------------------------------------------------------
// 10. Job / Task force de la IA (DAT_00522584, 7 x 50 x 0xc4; FUN_0040be04 crea)
// ----------------------------------------------------------------------------------------
struct Job {
    int32_t  goal;               // 0x00 TaskForceGoal (PTR_s_NO_TF_GOAL_004b6bd4)
    int32_t  status;             // 0x04 TaskForceStatus (PTR_s_NEED_SPACE_004b6c7c)
    int16_t  targetPlayer;       // 0x08 enemigo (-1 = "No Enemy")
    int16_t  owner;              // 0x0a jugador propietario
    int16_t  param1;             // 0x0c
    int16_t  param2;             // 0x0e
    Ptr32<Territory> destination;// 0x10 territorio destino ("No Destination"); save: índice (FUN_00460f24)
    int32_t  strengthWanted;     // 0x14 "Strength: %d/%d"
    uint8_t  unk_18[0x0c];       // 0x18
    uint16_t armyIds[16];        // 0x24 IDs globales de los ejércitos asignados
    Ptr32<Army> armies[16];      // 0x44 punteros (load: FindArmyByGlobalID(armyIds[i]); FUN_0040aebc valida)
    int32_t  parentJob;          // 0x84 índice del job padre ("Parent: %s %s"; 0 = ninguno)
    uint8_t  unk_88[0x3c];       // 0x88
};
static_assert(sizeof(Job) == 0xc4);
static_assert(offsetof(Job, armyIds) == 0x24);
static_assert(offsetof(Job, armies) == 0x44);
static_assert(offsetof(Job, parentJob) == 0x84);

// ----------------------------------------------------------------------------------------
// 11. Trabajo de ministro (listas por jugador en DAT_00522280, 7 cabeceras x 0x44 + nodos)
// ----------------------------------------------------------------------------------------
struct MinisterJob {
    int32_t  type;               // 0x00 MinisterJobType (cabecera de lista: 1 = HEAD_JOB)
    int32_t  minister;           // 0x04 Minister
    int32_t  priority;           // 0x08 "Job Type: %s Minister: %s Priority: %d"
    int32_t  unk_0c;
    int32_t  unk_10;
    Ptr32<MinisterJob> next;     // 0x14 (save: se escribe crudo; load: != 0 => sigue otro nodo)
    Ptr32<MinisterJob> prev;     // 0x18
    int32_t  param[3];           // 0x1c edificio/territorio/unidad/tecnología/material según type
    uint8_t  unk_28[0x1c];       // 0x28
};
static_assert(sizeof(MinisterJob) == 0x44);

// ----------------------------------------------------------------------------------------
// 12. Tecnología (DAT_004fbbac, 48 x 0x32; en fichero 0x12 bytes por entrada)
// ----------------------------------------------------------------------------------------
struct TechEntry {
    uint16_t knownMask;          // 0x00 bit i = jugador i la conoce (CalculatePlayersScores, GetBuildingTasks)
    uint16_t availableMask;      // 0x02 bit i = jugador i puede investigarla (0x7f en ficheros)
    uint16_t unk_04;             // 0x04 (no se guarda)
    uint16_t progress[7];        // 0x06 por jugador (FUN_00483d58 / FUN_00483f20 investigación)
    Ptr32<const char> name;      // 0x14 PTR_s_Nothing_004fbbc0 ...
    uint32_t descOffset;         // 0x18 múltiplo de 4 (FUN_0043c540 árbol de tecnologías)
    uint32_t unk_1c;             // 0x1c puntero constante 0x004f9bbc
    uint16_t level;              // 0x20 nivel 1..8 (FUN_0047c730 compara con la campaña)
    uint16_t cost;               // 0x22 coste de investigación (50..5000)
    uint16_t prereq[3];          // 0x24 tecnologías requeridas ("Requires")
    uint16_t unk_2a;
    int16_t  flag_2c;            // 0x2c 1 / -1
    uint16_t sprite;             // 0x2e
    uint16_t unk_30;
};
static_assert(sizeof(TechEntry) == 0x32);
static_assert(offsetof(TechEntry, name) == 0x14);
static_assert(offsetof(TechEntry, level) == 0x20);

struct TechSaved {               // FUN_0045fe58 / FUN_0045fecc
    uint16_t knownMask;          // TechEntry+0
    uint16_t availableMask;      // TechEntry+2
    uint16_t progress[7];        // TechEntry+6
};
static_assert(sizeof(TechSaved) == 0x12);

// ----------------------------------------------------------------------------------------
// 13. Event Log (DAT_00651cb4, 50 x 0x14; contador DAT_0065209c)
// ----------------------------------------------------------------------------------------
struct EventLogEntry {
    uint16_t type;               // 0x00 id de evento (FUN_0042278c -> tabla DAT_004fc90c paso 0x12)
    uint16_t unk_02;
    Ptr32<char> text;            // 0x04 texto en el pool PTR_DAT_004b7b54 (FUN_004234d4)
    uint32_t portrait;           // 0x08 FUN_004503f4(raza, tabla+0xc, ...) (no se guarda)
    int32_t  player;             // 0x0c jugador relacionado (FUN_004237d0 param_7)
    int32_t  param;              // 0x10 parámetro extra (FUN_004237d0 param_8)
};
static_assert(sizeof(EventLogEntry) == 0x14);

struct EventSaved {              // FUN_0046002c: cabecera + texto de textLen bytes (sin NUL, <= 0x3ff)
    uint16_t type;
    uint16_t textLen;
    int32_t  player;
    int32_t  param;
};
static_assert(sizeof(EventSaved) == 0xc);

// ----------------------------------------------------------------------------------------
// 14. Bloques fijos
// ----------------------------------------------------------------------------------------
struct RaceStats {               // DAT_00559e00, 0x380: modificadores por [fila][raza] (FUN_00441128 desde DAT_004fc50c)
    int16_t v[64][7];            // fila 24 = % población máxima (FUN_0046b0e4), 29/35/37/39/41/43 producción
};                               // por categoría de edificio (FUN_00447c2c), 51 espionaje, 61 mantenimiento
static_assert(sizeof(RaceStats) == 0x380);

struct RandomEvent {             // DAT_00654804, 25 x 28 = 700 (CreateRandomEvents, FUN_0047cad4)
    int32_t  type;               // 0x00 1..9 (índice en PTR_FUN_004dcab0); 0 = libre
    int32_t  unk_04;
    int32_t  turnsLeft;          // 0x08 = 0 al crear
    int32_t  unk_0c[4];
};
static_assert(sizeof(RandomEvent) == 28);

struct PlayerScore {             // DAT_00657df4, 7 x 6 = 0x2a (CalculatePlayersScores, FUN_0044b924)
    int32_t  score;              // 0x00 puntuación
    uint8_t  nukesUsed;          // 0x04 -100 puntos cada uno (FUN_0044b924 lo incrementa)
    uint8_t  unk_05;
};
static_assert(sizeof(PlayerScore) == 6);

struct Spy {                     // DAT_00654ac0, 7 x 25 x 8 = 0x578 (FUN_0047d49c "Scandal")
    int16_t  owner;              // 0x00 jugador que lo envió (-1 = libre)
    int16_t  territory;          // 0x02 territorio objetivo
    int16_t  mission;            // 0x04 índice en DAT_004dca60
    int16_t  turns;              // 0x06 /20 en el cálculo de riesgo
};
static_assert(sizeof(Spy) == 8);

struct BlackMarketState {        // DAT_005644f8, 7 x 8 = 0x38 (FUN_00450c9c init {0,-1}; FUN_00450c38)
    int32_t  pending;            // 0x00 1 = oferta Skirineen pendiente
    int32_t  turn;               // 0x04 turno de la oferta (-1)
};
static_assert(sizeof(BlackMarketState) == 8);

struct Continent {               // DAT_0055a820, 32 x 0x1a2 (FUN_004423b4; NO se guarda pero SaveJobs lo vuelca)
    int16_t  unk_00;
    int16_t  hasLand;            // 0x02
    uint16_t terrainMask;        // 0x04 bits por Terrain presentes
    uint16_t unk_06;
    uint32_t adjContinents;      // 0x08
    uint8_t  unk_0c[0x0a];
    int16_t  bonus;              // 0x16 (FUN_00427854)
    uint8_t  unk_18[0x18a];
};
static_assert(sizeof(Continent) == 0x1a2);

// ----------------------------------------------------------------------------------------
// 15. Territorio reducido del modo mapa (FUN_00460d84) - 0xaa
// ----------------------------------------------------------------------------------------
struct MapTerritory {
    char     name[25];           // Territory::name (strcpy; el resto basura de pila)
    uint8_t  terrain;            // Territory::terrain
    struct { uint16_t terrain; uint8_t value; uint8_t pad; } sites[36]; // BuildingSite::terrainFlags & 0xf, ::value
};
static_assert(sizeof(MapTerritory) == 0xaa);

// ----------------------------------------------------------------------------------------
// 16. Tablas estáticas del EXE (no se guardan; útiles para la reimplementación)
// ----------------------------------------------------------------------------------------
struct BuildingTypeDef {         // DAT_004f9dbc, 48 x 0x32 (decodificada en data_tables.h: dl2::data::kBuildingTypes)
    Ptr32<const char> name;      // 0x00
    uint16_t sprite;             // 0x04 indice base de sprite (FUN_0045ee88; +raza en viviendas/City Center/SeaHab/Kelp Farm)
    uint8_t  icon;               // 0x06 imagen en IMAG "BU01" (FUN_0041beac)
    uint8_t  category;           // 0x07 -> Building::category (FUN_0044d890)
    uint8_t  maxLabor;           // 0x08 trabajadores maximos (FUN_0044ba40; viviendas x RaceStats fila 24)
    uint8_t  size;               // 0x09 casillas: 1, 2 o 5 (FUN_0044d7b4)
    uint16_t buildLabor;         // 0x0a puntos de trabajo de construccion = Building::turnsLeft inicial (FUN_0044de9c cost[0], FUN_0044c718)
    uint16_t energyUse;          // 0x0c energia consumida por turno (FUN_0046b910, FUN_0044bddc)
    int16_t  taskRate[5];        // 0x0e rendimiento por ranura de tarea (FUN_0044eb4c: [0] construccion, [1..4] tasks)
    uint8_t  tasks[5];           // 0x18 id de tarea por ranura = BuildingTask+2 (tabla 0x509178; [0] siempre 0; GetBuildingTasks lee 1..4)
    uint8_t  units[10];          // 0x1d unidades construibles, 0 = fin (FUN_004383a4)
    uint8_t  techRequired;       // 0x27 TechId necesaria (FUN_0044de9c cost[12] "Tech: %s"; CanUpgradeBuilding)
    uint8_t  hitPoints;          // 0x28 resistencia al dano (FUN_004526b0, FUN_00451de4)
    uint8_t  unk_29;             // 0x29 siempre 0, sin lectores
    int32_t  productionQueue;    // 0x2a cola Territory::queues[] 1..5 (FUN_0044f3f0 tarea Build Units); 0 = ninguna
    int32_t  dialogAnim;         // 0x2e animacion del dialogo de produccion (FUN_0041ccb0 -> FUN_00482b38(4, id); -1 = ninguna)
};
static_assert(sizeof(BuildingTypeDef) == 0x32);

struct UnitTypeDef {             // PTR_s_No_Unit_004faf7c, 39 x 0x24 (decodificada en data_tables.h: dl2::data::kUnitTypes)
    Ptr32<const char> name;      // 0x00
    uint16_t combatSprite;       // 0x04 sprite de combate (LoadCombatSprites/BirthCombatSprites; fuertes = sprite del edificio)
    uint16_t moveAnim;           // 0x06 id de ANIM del vehiculo en combate (0 = infanteria por raza; FUN_0043d2d8)
    uint16_t portraitGroup;      // 0x08 grupo de imagenes del retrato (FUN_004382d0: 0x9f/0x91/0x98/0xa6/0xad)
    int8_t   portraitIndex;      // 0x0a indice dentro del grupo (+raza*N) (FUN_004382d0, FUN_00418660)
    uint8_t  unitClass;          // 0x0b -> Army::unitClass (FUN_00445d30); grupos de ataque/mantenimiento (FUN_00447c2c, FUN_0046b4d0)
    uint16_t buildLabor;         // 0x0c puntos de trabajo ("%d Labor"; FUN_0044ddf4 cost[0])
    int8_t   upkeep;             // 0x0e creditos de mantenimiento por turno (FUN_0046b4d0, FUN_00431734)
    int8_t   techRequired;       // 0x0f TechId necesaria (FUN_0044ddf4 cost[12])
    int8_t   moves;              // 0x10 puntos de movimiento -> Army::strength(+0x0a) (FUN_00447190; +1 con Transporters)
    int8_t   domain;             // 0x11 1 tierra, 2 mar, 3 aire, 6 anfibio (FUN_00445b94, CheckSubUnit)
    int8_t   unk_12;             // 0x12 sin lectores (4 infanteria, 2 blindados, 3 aire/mar, 0 fuertes)
    int8_t   attack;             // 0x13 ataque base (FUN_00447c2c x RaceStats filas 29/35/37/39/41/43)
    int8_t   defense;            // 0x14 defensa base (FUN_00447da4 x filas 30/36/38/40/42/44)
    int8_t   speed;              // 0x15 velocidad en combate (menor = mas rapido, -1 inmovil; FUN_00447f44 + fila 46)
    int8_t   rateOfFire;         // 0x16 cadencia: nombre = tabla 0x509a84[rof+1] (FUN_00448008, FUN_00431734)
    int8_t   range;              // 0x17 alcance de disparo al cuadrado (FUN_004480a8)
    int32_t  sound;              // 0x18 id de sonido de disparo (FUN_0043d2d8 -> FUN_00482ac4)
    uint8_t  unk_1c[8];          // 0x1c siempre 0
};
static_assert(sizeof(UnitTypeDef) == 0x24);

#pragma pack(pop)

// ----------------------------------------------------------------------------------------
// Estado global en memoria (equivalente a la sección DATA del EXE)
// ----------------------------------------------------------------------------------------
struct GameState {
    GameOptions      options;                       // DAT_0059f154.. (dispersos en el EXE)
    WorldParams      world;                         // DAT_004d5b10
    Player           players[kMaxPlayers];          // DAT_0059f160
    Tile             tiles[kMapMaxSize][kMapMaxSize]; // DAT_005a0550 (filas de 400 bytes)
    Territory        territories[kMaxTerritories];  // DAT_005a43d0 ([0] no se usa)
    Building         buildings[kMaxBuildings];      // DAT_005f0410
    Army             armies[kMaxArmies];            // DAT_00645370
    EventLogEntry    events[kMaxEvents];            // DAT_00651cb4
    Job              jobs[kMaxPlayers][kJobsPerPlayer]; // DAT_00522584
    Job              scratchJob1;                   // DAT_005220a4
    Job              scratchJob2;                   // DAT_00522168
    uint32_t         aiWarMask[kMaxPlayers];        // DAT_0052222c (FUN_00403350: bit = jugador)
    MinisterJob      ministerJobHeads[kMaxPlayers]; // DAT_00522280
    TechEntry        techs[kNumTechs];              // DAT_004fbbac
    RaceStats        raceStats;                     // DAT_00559e00
    Continent        continents[32];                // DAT_0055a820
    RandomEvent      randomEvents[kNumRandomEvents];// DAT_00654804
    PlayerScore      scores[kMaxPlayers];           // DAT_00657df4
    Spy              spies[kMaxPlayers][kSpiesPerPlayer]; // DAT_00654ac0
    BlackMarketState blackMarket[kMaxPlayers];      // DAT_005644f8
};

} // namespace dl2
