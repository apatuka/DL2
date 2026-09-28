// XenoIntro @ 0046ffec size=97 sig=undefined XenoIntro() cc=unknown
// callers: InitCYGame,WinMain
// callees: FUN_00415274,CreateWindowExA,FUN_00494def
// strings: \"XenoIntro\"

/* auto-named from string evidence: XenoIntro */

void XenoIntro(void)

{
  if (DAT_004d5978 == (HWND)0x0) {
    FUN_00494def(0);
    DAT_004d5978 = CreateWindowExA(8,s_XenoIntro_004d5967,s_CHECKSUM_SAV_004d5c2c + 0xc,0x56000000,0
                                   ,0,DAT_0058f1c0,DAT_0058f1c4,DAT_0058f1a4,(HMENU)0x0,DAT_0058f19c
                                   ,(LPVOID)0x0);
    FUN_00494def(1);
  }
  FUN_00415274(DAT_004d5978);
  return;
}

