// ShutdownGame @ 0046ced4 size=291 sig=undefined ShutdownGame() cc=unknown
// callers: WinMain
// callees: FUN_00441a44,FUN_00458bb0,FUN_0046ce10,DestroyWindow,FUN_0046cc48,SelectPalette,FUN_004a4113,FUN_0046ff98,FUN_004152c0,SavePrefs,PostQuitMessage,DeleteDC,ReleaseDC,FreeSmacker,FUN_004418e4
// strings: \"At end\\r\\n\"

/* Final cleanup at exit */

void ShutdownGame(void)

{
  FUN_004152c0();
  FUN_0046ce10(1);
  if (DAT_004d5978 != (HWND)0x0) {
    FUN_004a4113();
    DestroyWindow(DAT_004d5978);
    DAT_004d5978 = (HWND)0x0;
  }
  if (DAT_004d2360 != 0) {
    SelectPalette(DAT_004d597c,DAT_004d2364,0);
    FUN_00458bb0(DAT_004d2360);
    DAT_004d2360 = 0;
    DAT_004d2364 = (HPALETTE)0x0;
  }
  SavePrefs();
  if (DAT_0058f1b8 != 0) {
    FUN_00458bb0(DAT_0058f1b8);
    DAT_0058f1b8 = 0;
  }
  if (DAT_0058f1bc != 0) {
    FUN_00458bb0(DAT_0058f1bc);
    DAT_0058f1bc = 0;
  }
  if (DAT_0058f1b4 != 0) {
    FUN_00458bb0(DAT_0058f1b4);
    DAT_0058f1b4 = 0;
  }
  if (DAT_0058f1b0 != (HDC)0x0) {
    DeleteDC(DAT_0058f1b0);
    DAT_0058f1b0 = (HDC)0x0;
  }
  if (DAT_004d597c != (HDC)0x0) {
    ReleaseDC(DAT_0058f1a4,DAT_004d597c);
    DAT_004d597c = (HDC)0x0;
  }
  FUN_00441a44();
  FreeSmacker();
  FUN_0046cc48();
  FUN_004418e4(s_At_end_004d5c5c);
  if (DAT_0058f1a4 != (HWND)0x0) {
    DestroyWindow(DAT_0058f1a4);
    DAT_0058f1a4 = (HWND)0x0;
  }
  PostQuitMessage(0);
  FUN_0046ff98();
  return;
}

