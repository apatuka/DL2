// CreateGamePalette2 @ 00463944 size=150 sig=undefined CreateGamePalette2() cc=unknown
// callers: CreateMainWindow,FUN_00472e4c,FUN_004639dc
// callees: FUN_00458bb0,CreatePalette,RealizePalette,GetLastError,GetDC,SelectPalette,FUN_004637b4

/* Creates palette (variant used by CreateMainWindow) */

void CreateGamePalette2(void)

{
  UINT UVar1;
  
  if (DAT_004d597c == (HDC)0x0) {
    DAT_004d597c = GetDC(DAT_0058f1a4);
  }
  if (DAT_004d2360 != (HPALETTE)0x0) {
    SelectPalette(DAT_004d597c,DAT_004d2364,0);
    FUN_00458bb0(DAT_004d2360);
    DAT_004d2360 = (HPALETTE)0x0;
    DAT_004d2364 = (HPALETTE)0x0;
  }
  FUN_004637b4();
  DAT_004d2360 = CreatePalette((LOGPALETTE *)&DAT_004d1f5c);
  DAT_004d2364 = SelectPalette(DAT_004d597c,DAT_004d2360,0);
  UVar1 = RealizePalette(DAT_004d597c);
  if (UVar1 == 0xffffffff) {
    GetLastError();
  }
  return;
}

