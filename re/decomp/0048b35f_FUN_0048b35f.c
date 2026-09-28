// FUN_0048b35f @ 0048b35f size=132 sig=undefined FUN_0048b35f() cc=unknown
// callers: CYGame_CreateWindow
// callees: RealizePalette,ReleaseDC,CreatePalette,SelectPalette,GetDC,DeleteObject

void FUN_0048b35f(void)

{
  undefined4 uVar1;
  HDC hdc;
  HPALETTE pHVar2;
  int iVar3;
  undefined4 *puVar4;
  LOGPALETTE *pLVar5;
  LOGPALETTE local_408 [128];
  
  puVar4 = &DAT_0051b8e0;
  pLVar5 = local_408;
  for (iVar3 = 0x101; iVar3 != 0; iVar3 = iVar3 + -1) {
    uVar1 = *puVar4;
    pLVar5->palVersion = (short)uVar1;
    pLVar5->palNumEntries = (short)((uint)uVar1 >> 0x10);
    puVar4 = puVar4 + 1;
    pLVar5 = (LOGPALETTE *)pLVar5->palPalEntry;
  }
  iVar3 = 0;
  do {
    local_408[0].palPalEntry[iVar3].peRed = '\0';
    local_408[0].palPalEntry[iVar3].peGreen = '\0';
    local_408[0].palPalEntry[iVar3].peBlue = '\0';
    local_408[0].palPalEntry[iVar3].peFlags = '\x04';
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x100);
  hdc = GetDC((HWND)0x0);
  pHVar2 = CreatePalette(local_408);
  if (pHVar2 != (HPALETTE)0x0) {
    pHVar2 = SelectPalette(hdc,pHVar2,0);
    RealizePalette(hdc);
    pHVar2 = SelectPalette(hdc,pHVar2,0);
    DeleteObject(pHVar2);
  }
  ReleaseDC((HWND)0x0,hdc);
  return;
}

