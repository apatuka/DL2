// CreateGamePalette @ 004636cc size=106 sig=undefined CreateGamePalette() cc=unknown
// callers: FUN_0046cc6c
// callees: CreatePalette,FUN_00458bb0,RealizePalette,ReleaseDC,GetDC,SelectPalette

/* Creates and realizes the GDI palette */

void CreateGamePalette(void)

{
  undefined1 *puVar1;
  HDC hdc;
  HPALETTE pHVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar1 = &DAT_004d1f60;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 4;
    iVar3 = iVar3 + 1;
    puVar1 = puVar1 + 4;
  } while (iVar3 < 0x100);
  hdc = GetDC((HWND)0x0);
  pHVar2 = CreatePalette((LOGPALETTE *)&DAT_004d1f5c);
  if (pHVar2 != (HPALETTE)0x0) {
    pHVar2 = SelectPalette(hdc,pHVar2,0);
    RealizePalette(hdc);
    pHVar2 = SelectPalette(hdc,pHVar2,0);
    FUN_00458bb0(pHVar2);
  }
  ReleaseDC((HWND)0x0,hdc);
  return;
}

