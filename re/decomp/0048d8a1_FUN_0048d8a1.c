// FUN_0048d8a1 @ 0048d8a1 size=125 sig=undefined FUN_0048d8a1() cc=unknown
// callers: FUN_00463bcc
// callees: GlobalLock,GlobalUnlock,FUN_0048d76a,GetPaletteEntries

HGLOBAL FUN_0048d8a1(HPALETTE param_1)

{
  UINT UVar1;
  LPVOID pvVar2;
  int iVar3;
  HGLOBAL hMem;
  tagPALETTEENTRY local_404 [256];
  
  hMem = (HGLOBAL)0x0;
  UVar1 = GetPaletteEntries(param_1,0,0x100,local_404);
  if (UVar1 != 0) {
    hMem = (HGLOBAL)FUN_0048d76a(UVar1,0);
    if (hMem != (HGLOBAL)0x0) {
      pvVar2 = GlobalLock(hMem);
      for (iVar3 = 0; iVar3 < *(short *)((int)pvVar2 + 2); iVar3 = iVar3 + 1) {
        *(BYTE *)((int)pvVar2 + iVar3 * 4 + 8) = local_404[iVar3].peRed;
        *(BYTE *)((int)pvVar2 + iVar3 * 4 + 9) = local_404[iVar3].peGreen;
        *(BYTE *)((int)pvVar2 + iVar3 * 4 + 10) = local_404[iVar3].peBlue;
      }
      GlobalUnlock(hMem);
    }
  }
  return hMem;
}

