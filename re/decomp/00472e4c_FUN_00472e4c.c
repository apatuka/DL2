// FUN_00472e4c @ 00472e4c size=26 sig=undefined FUN_00472e4c() cc=unknown
// callers: @MainWndProc$qqspvuiuil,FUN_00472f2c,FUN_00472f18,FUN_00472e9c,FUN_00472ed0
// callees: InvalidateRect,CreateGamePalette2,FUN_004879fc

void FUN_00472e4c(void)

{
  CreateGamePalette2();
  InvalidateRect(DAT_0058f1a4,(RECT *)0x0,0);
  FUN_004879fc();
  return;
}

