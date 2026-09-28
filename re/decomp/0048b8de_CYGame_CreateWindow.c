// CYGame_CreateWindow @ 0048b8de size=342 sig=undefined CYGame_CreateWindow() cc=unknown
// callers: FUN_00493564
// callees: LoadCursorA,GetStockObject,CreateWindowExA,RegisterClassA,FUN_0048b35f,UpdateWindow,ShowWindow,CYGame_InitDirectDraw,LoadIconA,GetSystemMetrics
// strings: \"CYGame\"|\"Cyberlore Game\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Registers/creates the "CYGame" window */

undefined4 CYGame_CreateWindow(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  DWORD dwStyle;
  int iVar3;
  HWND pHVar4;
  HMENU hMenu;
  HINSTANCE pHVar5;
  LPVOID lpParam;
  WNDCLASSA local_30;
  int local_8;
  
  local_30.style = 0xb;
  local_30.lpfnWndProc = FUN_0048b1c0;
  local_30.cbClsExtra = 0;
  local_30.cbWndExtra = 0;
  local_30.hInstance = DAT_0065eb98;
  local_30.hIcon = LoadIconA(DAT_0065eb98,(LPCSTR)0x7f00);
  local_30.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_30.hbrBackground = GetStockObject(4);
  local_30.lpszMenuName = s_CYGame_0051bd6c;
  local_30.lpszClassName = s_CYGame_0051bd73;
  RegisterClassA(&local_30);
  _DAT_0051b828 = 1;
  DAT_0051b82c = param_4;
  if (param_4 == 0) {
    if (param_1 == 0) {
      param_1 = GetSystemMetrics(0);
    }
    if (param_2 == 0) {
      param_2 = GetSystemMetrics(1);
    }
    local_8 = param_2;
    FUN_0048b35f();
  }
  else {
    local_8 = param_2;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  pHVar4 = (HWND)0x0;
  pHVar5 = DAT_0065eb98;
  if (param_4 == 0) {
    iVar1 = GetSystemMetrics(0x21);
    iVar3 = GetSystemMetrics(4);
    iVar3 = iVar1 * 2 + iVar3;
  }
  else {
    iVar3 = 0;
  }
  iVar3 = iVar3 + local_8;
  if (param_4 == 0) {
    iVar1 = GetSystemMetrics(0x20);
    iVar1 = iVar1 * 2;
  }
  else {
    iVar1 = 0;
  }
  dwStyle = 0x80000000;
  if (param_4 == 0) {
    dwStyle = 0xcf0000;
  }
  pHVar4 = CreateWindowExA(0,s_CYGame_0051bd7a,s_Cyberlore_Game_0051bd81,dwStyle,0,0,iVar1 + param_1
                           ,iVar3,pHVar4,hMenu,pHVar5,lpParam);
  if (pHVar4 == (HWND)0x0) {
    uVar2 = 0;
  }
  else {
    ShowWindow(pHVar4,DAT_0065eb9c);
    UpdateWindow(pHVar4);
    uVar2 = CYGame_InitDirectDraw(pHVar4,param_4,param_1,local_8,param_3);
  }
  return uVar2;
}

