// FUN_0048d82a @ 0048d82a size=119 sig=undefined FUN_0048d82a() cc=unknown
// callers: 
// callees: GlobalLock,GlobalUnlock,CreatePalette

HPALETTE FUN_0048d82a(HGLOBAL param_1)

{
  undefined4 uVar1;
  LPVOID pvVar2;
  HPALETTE pHVar3;
  int iVar4;
  undefined4 *puVar5;
  LOGPALETTE *pLVar6;
  LOGPALETTE local_408 [128];
  
  puVar5 = &DAT_0051bde8;
  pLVar6 = local_408;
  for (iVar4 = 0x101; iVar4 != 0; iVar4 = iVar4 + -1) {
    uVar1 = *puVar5;
    pLVar6->palVersion = (short)uVar1;
    pLVar6->palNumEntries = (short)((uint)uVar1 >> 0x10);
    puVar5 = puVar5 + 1;
    pLVar6 = (LOGPALETTE *)pLVar6->palPalEntry;
  }
  pvVar2 = GlobalLock(param_1);
  local_408[0].palNumEntries = *(WORD *)((int)pvVar2 + 2);
  for (iVar4 = 0; iVar4 < *(short *)((int)pvVar2 + 2); iVar4 = iVar4 + 1) {
    local_408[0].palPalEntry[iVar4].peRed = *(BYTE *)((int)pvVar2 + iVar4 * 4 + 8);
    local_408[0].palPalEntry[iVar4].peGreen = *(BYTE *)((int)pvVar2 + iVar4 * 4 + 9);
    local_408[0].palPalEntry[iVar4].peBlue = *(BYTE *)((int)pvVar2 + iVar4 * 4 + 10);
    local_408[0].palPalEntry[iVar4].peFlags = '\x04';
  }
  pHVar3 = CreatePalette(local_408);
  GlobalUnlock(param_1);
  return pHVar3;
}

