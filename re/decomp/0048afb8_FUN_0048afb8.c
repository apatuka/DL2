// FUN_0048afb8 @ 0048afb8 size=43 sig=undefined FUN_0048afb8() cc=unknown
// callers: CYGame_InitDirectDraw
// callees: FUN_0048af43,MessageBoxA,DestroyWindow
// strings: \"Cyberlore Game\"|\"DirectDraw Init FAILED\"

undefined4 FUN_0048afb8(HWND param_1)

{
  FUN_0048af43();
  MessageBoxA(param_1,s_DirectDraw_Init_FAILED_0051bce4,s_Cyberlore_Game_0051bcfb,0);
  DestroyWindow(param_1);
  return 0;
}

