// smenu.h - sistema de menus/pantallas "SMenu" de CYLib (0x49B000-0x4A6800): carga de SMNU, modelo de items
// con los ids/flags/estados originales, mensajes (FUN_0049eb44 / FUN_004a43da), dibujado (FUN_004a2078),
// deteccion de raton (FUN_0049f4c2) y procesado de eventos (FUN_004a2cb5).
#pragma once
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "engine/engine_types.h"
#include "engine/font.h"
#include "engine/offport.h"
#include "engine/resources.h"

namespace dl2::engine {

class SMenu;
struct SMenuItem;

// Tipos de item (+0x1c).
enum SMenuItemType : int {
    kItemButton = 0,
    kItemCheckBox = 1,
    kItemRadio = 2,
    kItemPicture = 3,
    kItemListBox = 4,     // lista de cadenas STRT (desplegable si kind == 1)
    kItemText = 5,        // texto estatico o campo de edicion (flags & kItemFlagEdit)
    kItemGrid = 6,        // rejilla de celdas con texto/imagen
    kItemScrollBar = 9,
    kItemHotKey = 10,     // sin representacion grafica
};

// Clase de grafico (bits 0-4 de +0x24, opcode 10).
enum SMenuGraphicKind : uint32_t {
    kGraphicPlain = 0,    // rectangulo con bordes (o lista simple en tipo 4)
    kGraphicCombo = 1,    // tipo 4: desplegable
    kGraphicImag = 2,     // imagen IMAG (id en imageId)
    kGraphicPict = 4,     // PICT (offport)
    kGraphicNone = 8,
    kGraphicTextOnly = 0x10,
};
// Flags (+0x24, opcode 10).
enum SMenuItemFlags : uint32_t {
    kItemFlagKindMask = 0x1f,
    kItemFlagVertical = 0x40,       // tipo 9: barra vertical
    kItemFlagEdit = 0x80,           // tipo 5: editable
    kItemFlagRepeatScroll = 0x200000,
    kItemFlagSubIndexMsg = 0x200000,
    kItemFlagNoEndButtons = 0x80000000,
};
// Estado (+0x28, opcode 3).
enum SMenuItemState : uint32_t {
    kStateChecked = 0x1,
    kStateReturnsId = 0x2,          // al pulsarlo el menu devuelve su id
    kStateDisabled = 0x4,           // dibujado con la capa 2, no responde
    kStateHighlight = 0x10,         // pulsado / resaltado (capa 1)
    kStateStatic = 0x80,            // no recibe raton
    kStateAnimated = 0x100,         // avanza de columna cada animPeriod ms
    kStateAlignMask = 0x438000,     // colocacion del grafico/texto (FUN_0049fa76)
    kStateAlignTopLeft = 0x8000,
    kStateAlignTop = 0x10000,
    kStateAlignTopRight = 0x18000,
    kStateAlignRight = 0x20000,
    kStateAlignBottomRight = 0x28000,
    kStateAlignBottom = 0x30000,
    kStateAlignBottomLeft = 0x38000,
    kStateAlignLeft = 0x400000,
    kStateAlignCenter = 0x408000,
    kStateFocus = 0x800000,
};
// Flags del menu (+0x1c, opcode 3 del registro 1000).
enum SMenuFlags : uint32_t {
    kMenuNoBackground = 0x2,
    kMenuTooltips = 0x4,
    kMenuDisabled = 0x8,      // FUN_004a3fa6
    kMenuRunLoop = 0x10,      // dentro de SMenu::run (las teclas llegan por keyPending)
    kMenuPassKeys = 0x40,     // no consume las teclas que ningun item usa
    kMenuHidden = 0x80,       // FUN_004a3fcd
};

// Mensajes (FUN_0049eb44 / FUN_004a43da).
enum SMenuMsg : int {
    kMsgGetRect = 1, kMsgDispose = 2, kMsgDraw = 3, kMsgAnimate = 4, kMsgInit = 6, kMsgSetProc = 7,
    kMsgInvalidate = 8, kMsgSetHighlight = 9, kMsgSetDisabled = 10, kMsgSetChecked = 0xb, kMsgIsChecked = 0xc,
    kMsgSetRect = 0xd, kMsgGetText = 0xe, kMsgSetText = 0xf, kMsgGetFont = 0x10, kMsgSetFont = 0x11,
    kMsgGetColors = 0x12, kMsgSetColors = 0x13, kMsgGetTextFlags = 0x15, kMsgSetTextFlags = 0x16,
    kMsgGetRowHeight = 0x17, kMsgGetCount = 0x18, kMsgDrawCell = 0x19, kMsgGetColWidth = 0x1a,
    kMsgSelect = 0x1b, kMsgSelectRange = 0x1c, kMsgGetSubRect = 0x1d, kMsgGetColumns = 0x1e,
    kMsgGetSubState = 0x1f, kMsgScrollTo = 0x21, kMsgNextSelected = 0x22, kMsgSetCellText = 0x23,
    kMsgSetCellRect = 0x24, kMsgSetCellData = 0x25, kMsgInsertCell = 0x26, kMsgDeleteCell = 0x27,
    kMsgGetScrollInfo = 0x28, kMsgSetScrollInfo = 0x29, kMsgScrollLineUp = 0x2a, kMsgScrollLineDown = 0x2b,
    kMsgScrollPageUp = 0x2c, kMsgScrollPageDown = 0x2d, kMsgScrollChanged = 0x2e, kMsgPress = 0x2f,
    kMsgFilterKey = 0x30, kMsgLink = 0x31, kMsgSync = 0x32, kMsgGetVisible = 0x33, kMsgSetFocus = 0x34,
    kMsgGetCellText = 0x35, kMsgGetCellRect = 0x36, kMsgGetCellData = 0x37, kMsgGetTooltip = 0x38,
    kMsgSetTooltip = 0x39, kMsgCellSelecting = 0x3a, kMsgCellSelected = 0x3b, kMsgShow = 0x3c,
    kMsgPlaySound = 0x3d, kMsgSetSound = 0x3e, kMsgGetGraphicId = 0x3f, kMsgSetGraphic = 0x40,
    kMsgGetImageIndex = 0x41, kMsgSetImageIndex = 0x42, kMsgGetFlags = 0x43, kMsgSetGraphicKind = 0x44,
    kMsgRelease = 0x45, kMsgSetNumber = 0x46,
};

// Procedimiento de item (+0x40): devuelve != 0 si trata el mensaje.
using ItemProc = std::function<uint32_t(SMenuItem& item, int msg, uint32_t param, void* ptr)>;
// Hook de rectangulo/fondo del menu (+0x5c): op 1 = ajustar rect, op 3 = dibujar fondo (!= 0 si lo hizo).
using MenuHook = std::function<uint32_t(SMenu& menu, int op, void* ptr)>;
// Hook de teclado del menu (+0x58): op 0 = obtener tecla, 1/2 = consumir, 3 = procesar (!= 0 si la trato).
using KeyHook = std::function<uint32_t(SMenu& menu, int op, uint32_t key)>;

// Informacion de barra de desplazamiento (mensajes 0x28/0x29): campos con bit de mascara.
struct ScrollInfo {
    uint32_t mask = 0;   // 1 = pos, 2 = min, 4 = max, 8 = page
    int pos = 0, minValue = 0, maxValue = 0, page = 0;
};

// Evento de raton que se pasa a los items (FUN_004a2847 / FUN_004a2962).
struct PressEvent {
    int x = 0, y = 0;
    int sub = 0, subX = 0, subY = 0;   // sub-elemento (fila de lista, parte de barra...) y offset dentro de el
    uint32_t buttons = 0;             // 1 izq, 2 der, 8 teclado, 0x10 doble clic, 0x20 arrastre (repeticion)
};

// Celda de un item tipo 6 (0x2c bytes en el original).
struct GridCell {
    uint32_t flags = 0;       // bit0 seleccionada, bits 2-3 deshabilitada
    int data = 0;             // +8 (dato de usuario)
    std::string text;         // +0x10
    struct Graphic {          // +0x14 (0x18 bytes): imagen IMAG asociada (opcodes 0xc/0xd/0x19/0x1a)
        uint32_t unused0 = 0, imag = 0, imageId = 0, layer = 0, col = 0, unused5 = 0;
    } graphic;
};

struct SMenuItem {
    SMenu* menu = nullptr;         // +8
    int x = 0, y = 0;              // +0xc/+0x10 (relativos al menu; -1 = centrar)
    int h = 0, w = 0;              // +0x14/+0x18 (-1 = tamano del grafico)
    int type = kItemButton;        // +0x1c
    uint32_t param = 0;            // +0x20 (opcode 4): grupo de radio / indice seleccionado de lista
    uint32_t flags = 0;            // +0x24 (opcode 10)
    uint32_t state = 0;            // +0x28 (opcode 3)
    uint32_t hotkey = 0;           // +0x2c (opcode 5)
    uint32_t id = 0;               // +0x30 (opcode 6)
    std::string text;              // +0x34 (opcodes 1/7)
    bool hasText = false;
    ResPtr graphic;                // +0x38 (IMAG o PICT)
    OffPortPtr picture;            // PICT decodificado (kind 4)
    FontPtr font;                  // +0x3c (opcode 0x12)
    ItemProc proc;                 // +0x40
    uint32_t textFlags = 0;        // +0x44 (opcode 0x14): flags de TextBlock
    int value = 0;                 // +0x48 (opcode 0x13): posicion de la barra / valor
    int thumbPos = 0;              // +0x4c
    int frame = 0;                 // +0x50: columna de animacion (o STRT de la lista en tipo 4)
    ResPtr listStrt;               // tipo 4: tabla de cadenas
    uint32_t imageId = 0;          // +0x54 (opcode 0xd): id dentro del IMAG
    int animPeriod = 0;            // +0x58 (opcode 0xe)
    uint32_t animNext = 0;         // +0x5c
    int loop = 0;                  // +0x60 (opcode 0xf)
    int p68 = 0;                   // +0x68 (opcode 0x11)
    int rowHeight = 0;             // +0x6c (opcode 0x1c)
    int colWidth = 0;              // +0x70 (opcode 0x1b)
    int cellImageWidth = 0;        // +0x74 (opcode 0x1d)
    int columns = 0;               // +0x78 (opcode 0x1e)
    int listOffX = 0, listOffY = 0;  // +0x7c/+0x80
    int listWidth = 0;             // +0x88
    int listCount = 0;             // +0x8c
    int listSel = 0;               // +0x90 (indice seleccionado + 1)
    std::unique_ptr<TextBlock> textBlock;   // +0x94 (tipo 5)
    std::string editBuffer;                 // tipo 5 editable: texto propio
    std::vector<GridCell> cells;            // +0x94 (tipo 6)
    int scrollTop = 0;             // +0x98 (tipo 6: primera celda visible)
    ColorRef colors[6][3] = {};    // +0x9c(A) +0xa8(B) +0xb4(C) +0xc0(D) +0xcc(E) +0xd8(F), por estado 0..2
    ResPtr palette;                // +0xe4 (opcode 0xb)
    int rangeMin = 0, rangeMax = 0;  // +0xe8/+0xec (opcodes 0x1f/0x20)
    int pressSub = 0;              // +0xf0
    int pageSize = 0;              // +0xf4
    uint32_t caret = 0;            // +0xf8 (bit31 visible, bit30 fase)
    SMenuItem* linked = nullptr;   // +0xfc (barra <-> lista)
    std::string tooltip;           // +0x100 (opcode 0x21)
    int visible = 1;               // +0x104 (contador de show/hide)
    uint32_t buttonMask = 9;       // +0x108 (opcode 0x26): botones que acepta (1 izq, 2 der, 8 teclado)
    int sounds[3] = {-1, -1, -1};  // +0x10c.. (opcodes 0x27/0x28): WAVE de pulsar/soltar/otro (-1 = del menu)
    uint32_t graphicId = 0;        // +0x11c: id del IMAG/PICT
    int extra[4] = {0, 0, 0, 0};   // +0x120.. (opcode 0x2a)

    // Ayudas
    int stateIndex() const;                       // FUN_0049eafa: 0 normal, 1 resaltado, 2 deshabilitado
    int layerIndex() const;                       // FUN_0049fc69: stateIndex + 3 si esta marcado (tipos 1/2)
    uint32_t graphicKind() const { return flags & kItemFlagKindMask; }
    bool isChecked() const { return (state & kStateChecked) != 0; }
    bool hasFocus() const { return (state & kStateFocus) != 0; }
};

class SMenu {
public:
    // FUN_004a3de6: carga el SMNU `id` (4 chars como u32, p.ej. makeTag("D000")) de las librerias abiertas.
    static std::unique_ptr<SMenu> load(uint32_t id, int lib = 0);
    // FUN_004a3d26: construye un menu a partir de una lista de palabras SMNU en memoria.
    static std::unique_ptr<SMenu> fromWords(std::span<const uint32_t> words, Tag tag = 0xffffffff, int lib = 0);
    ~SMenu();   // FUN_004a4025

    // FUN_004a2004: coloca (centra si x/y == -1), inicializa los items y marca todo para redibujar.
    void show();
    // FUN_004a2078: dibuja el menu completo en su port (o en el port actual si no tiene).
    void draw();
    // FUN_004a0f18: dibuja un item.
    void drawItem(SMenuItem& item);
    // FUN_0049f83e: invalida el rectangulo del menu (se acumula en la lista de rectangulos sucios).
    void invalidate();
    void invalidateItem(SMenuItem& item);   // FUN_0049f7c9

    // FUN_004a2cb5: procesa raton/teclado; *hoverId recibe el id del item bajo el raton (0 si ninguno).
    // Devuelve true mientras hay un boton pulsado sobre el menu. El id seleccionado se obtiene con result().
    bool process(uint32_t* hoverId);
    // FUN_004a32d7 / FUN_004a3329: bucle sincrono que devuelve el id del item activado (o 0 si `stop` se activa).
    uint32_t run(const std::function<bool()>& pumpAndPresent);
    uint32_t result() const { return result_; }
    void clearResult() { result_ = 0; }

    // Busqueda (FUN_004a1150): por id (FUN_004a10d0) o por indice (FUN_004a110f).
    SMenuItem* itemById(uint32_t id);
    SMenuItem* itemByIndex(int index);
    int itemIndex(const SMenuItem* item) const;   // FUN_0049551a
    std::vector<std::unique_ptr<SMenuItem>>& items() { return items_; }
    // FUN_0049f4c2: item bajo (x,y) en coordenadas de pantalla (sub = fila/parte); nullptr si ninguno.
    SMenuItem* hitTest(int x, int y, int* sub = nullptr, int* subX = nullptr, int* subY = nullptr);
    // FUN_0049f715 / FUN_0049f696: foco de teclado.
    SMenuItem* focusedItem();
    void setFocus(SMenuItem* item);
    // FUN_0049f752: siguiente/anterior item enfocable (state bit 0x800000 no, +0x2b bit0 = 0x1000000 "focusable").
    SMenuItem* nextFocusable(SMenuItem* from, bool backwards);

    // FUN_0049eb44: envia un mensaje al item (proc propio o gestor por defecto FUN_004a43da).
    uint32_t sendMessage(SMenuItem* item, int msg, uint32_t param = 0, void* ptr = nullptr);
    uint32_t sendMessage(uint32_t itemId, int msg, uint32_t param = 0, void* ptr = nullptr) { return sendMessage(itemById(itemId), msg, param, ptr); }
    // FUN_004a19b4 / FUN_004a1c75: fija / lee un atributo del item con el numero de opcode SMNU.
    bool setAttribute(SMenuItem* item, int opcode, uint32_t value);
    bool getAttribute(SMenuItem* item, int opcode, uint32_t* value);

    // FUN_0049f09b: rectangulo del item en pantalla (o del desplegable si esta abierto).
    Rect itemRect(const SMenuItem& item) const;
    // FUN_0049f22b: rectangulo del menu en pantalla (aplica el hook op 1).
    Rect menuRect();
    // FUN_004a228a / FUN_004a2307 / FUN_0049f8a1: estado.
    void setHighlight(SMenuItem* item, int sub, bool on);
    void setDisabled(SMenuItem* item, bool on);
    void setChecked(SMenuItem* item, bool on);   // FUN_0049f947 (radio: desmarca el grupo)
    // FUN_004a3fa6 / FUN_004a3fcd
    void setEnabled(bool on) { if (on) flags &= ~uint32_t(kMenuDisabled); else flags |= kMenuDisabled; }
    void setHidden(bool on);

    // FUN_0049e638: colores del menu a partir de una paleta (entradas 0x10.., 0x20.., 0x30.., 0x40..).
    void colorsFromPalette(const ColorTable& pal);

    // Reproduccion de sonidos (mensaje 0x3d): id de WAVE de dl2sound.cam.
    static void setSoundPlayer(std::function<void(uint32_t waveId)> fn);
    // Lista global de menus (DAT_0051e384): el primero de la lista es el "de arriba".
    static std::vector<SMenu*>& all();
    // Rectangulos sucios acumulados por invalidate() (FUN_004a60b1); redrawDirty los redibuja y vacia.
    static std::vector<Rect>& dirtyRects();
    static void addDirty(const Rect& r);
    static void redrawDirty();     // FUN_004a322d: redibuja todos los menus visibles en los rects sucios

    // Campos del menu (mismos offsets que el original)
    int x = 0, y = 0, h = 0, w = 0;     // +8 +0xc +0x10 +0x14
    uint32_t flags = 0;                 // +0x1c
    uint32_t menuParam = 0;             // +0x20 (opcode 10): 1 = sin fondo por defecto (FUN_004a10b3)
    uint32_t keyPending = 0;            // +0x2c
    Tag tag = 0;                        // +0x30
    uint32_t param34 = 0;               // +0x34 (opcode 0xc)
    FontPtr font;                       // +0x38 (opcode 0x12)
    OffPort* port = nullptr;            // +0x3c (nullptr = pantalla)
    ResPtr palette;                     // +0x50 (opcode 0xb)
    ResPtr strt;                        // +0x54
    KeyHook keyHook;                    // +0x58
    MenuHook hook;                      // +0x5c
    std::function<void(SMenu&, const Rect&)> invalidateHook;   // +0x60
    bool initialized = false;           // +0x64
    SMenuItem* active = nullptr;        // +0x68 (item pulsado / activo)
    SMenuItem* keyItem = nullptr;       // +0x6c
    SMenuItem* keyActivated = nullptr;  // +0x70
    SMenuItem* pressed = nullptr;       // +0x74
    SMenuItem* clicked = nullptr;       // +0x78
    SMenuItem* hover = nullptr;         // +0x7c
    uint32_t pressButtons = 0;          // +0x80
    int hoverSub = 0;                   // +0x84
    int pressSub = 0, pressSubX = 0, pressSubY = 0;   // +0x88 +0x8c +0x90
    int pressValue = 0;                 // +0x98
    ColorRef colors[11][3] = {};        // +0x9c(fill) +0xa8(light) +0xb4(dark) +0xc0(textFg idx) +0xcc(selBack idx)
                                        // +0xd8(selText idx) +0xe4(textBg idx) +0xf0(bg) +0xfc(bgLight) +0x108(bgDark) +0x114(check)
    int sounds[3] = {-1, -1, -1};       // +0x120.. (opcodes 0x27/0x28)
    int lib = 0;

    enum ColorSet { kFill = 0, kLight = 1, kDark = 2, kTextFg = 3, kSelBack = 4, kSelText = 5, kTextBg = 6, kBg = 7, kBgLight = 8, kBgDark = 9, kCheck = 10 };

private:
    SMenu() = default;
    bool parseItems(std::span<const uint32_t> words);           // FUN_004a3533
    void parseMenuRecord(std::span<const uint32_t> words);      // FUN_004a39f7
    void parseGridCells(SMenuItem& it, const uint32_t*& p, const uint32_t* end);   // FUN_0049d315
    void layoutItem(SMenuItem& it);                             // FUN_004a1eb4
    void disposeItem(SMenuItem& it);                            // FUN_004a3ea0
    uint32_t defaultProc(SMenuItem& it, int msg, uint32_t param, void* ptr);   // FUN_004a43da
    void drawItemDefault(SMenuItem& it);                        // FUN_004a0e79
    void drawButton(SMenuItem& it);      // FUN_004a016e
    void drawCheckBox(SMenuItem& it);    // FUN_004a03cf
    void drawRadio(SMenuItem& it);       // FUN_004a060f
    void drawPicture(SMenuItem& it);     // FUN_004a034a
    void drawListBox(SMenuItem& it);     // FUN_004a08c5
    void drawTextItem(SMenuItem& it);    // FUN_0049e47a
    void drawGrid(SMenuItem& it);        // FUN_0049da81
    void drawGridCell(SMenuItem& it, int index, const Rect& r);   // FUN_0049d7f4
    void drawScrollBar(SMenuItem& it);   // FUN_0049c710
    void drawGraphic(SMenuItem& it, const Rect& r);       // FUN_0049fe03
    void drawGraphicText(SMenuItem& it, const Rect& r);   // FUN_0049ff48
    void drawButtonText(const char* text, int state);     // FUN_0049f9c0
    bool graphicSize(SMenuItem& it, int layer, uint32_t imageId, int col, int* w, int* h);   // FUN_0049fca2
    void drawImagCell(SMenuItem& it, const Rect& clipRect, int x, int y, int layer, uint32_t imageId, int col);  // FUN_0049fd2e
    bool selectFont(SMenuItem& it);      // FUN_0049eb9f
    void animate();                      // FUN_004a26e8
    void pressItem(SMenuItem& it, PressEvent& ev);    // FUN_004a2847
    void releaseItem(SMenuItem& it, const PressEvent& ev);   // FUN_004a2962
    void dragItem(SMenuItem& it, const PressEvent& ev);      // FUN_004a29cb
    bool itemStillHit(SMenuItem& it, int x, int y, const PressEvent& ev);   // FUN_004a2a27
    bool activateItem(SMenuItem& it, uint32_t key);   // FUN_004a2376
    void sendSubIndex(SMenuItem& it, int sub);       // FUN_004a2238
    void hoverSound(SMenuItem& it);                  // FUN_004a2c32
    SMenuItem* findHotkey(uint32_t key);             // FUN_004a240f
    bool giveKeyToFocused(uint32_t key);             // FUN_004a2498
    uint32_t keyHookCall(int op, uint32_t key);      // FUN_004a2be7 / FUN_004a2ac6
    int subHitTest(SMenuItem& it, int x, int y, int* subX, int* subY);   // FUN_0049f31e
    Rect subRect(SMenuItem& it, int sub);   // FUN_0049f28c
    void playSound(SMenuItem& it, int kind);   // FUN_004a1555
    // tipo 4/5/6/9
    Rect listRowRect(SMenuItem& it, int row);           // FUN_0049ebfb (tipo 4)
    void textBlockFor(SMenuItem& it);                   // FUN_0049ddf8
    bool editKey(SMenuItem& it, uint32_t key);          // FUN_0049e007
    bool gridKey(SMenuItem& it, uint32_t key);          // FUN_0049cd32
    int gridRowHeight(SMenuItem& it);                   // FUN_0049d58b
    int gridColWidth(SMenuItem& it);                    // FUN_0049d5c5
    int gridColumns(SMenuItem& it);                     // FUN_0049d5dd
    int gridVisibleRows(SMenuItem& it);                 // FUN_0049d06a
    int gridScrollTo(SMenuItem& it, int mode, int value);   // FUN_0049cf41
    int gridSelect(SMenuItem& it, int from, int to, int mode);   // FUN_0049d5e9
    void scrollPartRect(SMenuItem& it, int part, Rect& r);   // FUN_0049bb73
    void scrollThumbSize(SMenuItem& it, int* w, int* h);     // FUN_0049ba80
    void scrollUpdateThumb(SMenuItem& it, bool redraw);      // FUN_0049c244
    int scrollHitPart(SMenuItem& it, int x, int y);          // FUN_0049c45d
    bool scrollDragThumb(SMenuItem& it, int x, int y);       // FUN_0049c14c
    int scrollValueFromThumb(SMenuItem& it);                 // FUN_0049c313
    void scrollByPart(SMenuItem& it, int part, uint32_t buttons);   // FUN_0049cc43
    void scrollSetValue(SMenuItem& it, const ScrollInfo& si);       // FUN_0049b7f0
    void syncLinked(SMenuItem& it, bool fromScroll);         // FUN_004a4156

    std::vector<std::unique_ptr<SMenuItem>> items_;
    uint32_t result_ = 0;   // +0x94
    static std::function<void(uint32_t)> soundPlayer_;
};

// Teclas especiales del teclado CYLib (FUN_0048d920): valor bajo de 16 bits; los modificadores van en los bits
// altos (4 shift, 8 ctrl, 0x4000 alt) desplazados 16.
enum CyKey : uint32_t {
    kKeyPageUp = 0x101, kKeyRight = 0x102, kKeyPageDown = 0x103, kKeyDown = 0x104, kKeyEnd = 0x105,
    kKeyLeft = 0x106, kKeyHome = 0x107, kKeyUp = 0x108, kKeyInsert = 0x109, kKeyDelete = 0x10a,
    kKeyF1 = 0x110,
    kKeyModShift = 0x40000, kKeyModCtrl = 0x80000, kKeyModAlt = 0x40000000,
};

}  // namespace dl2::engine
