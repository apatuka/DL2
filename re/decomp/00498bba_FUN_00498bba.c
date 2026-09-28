// FUN_00498bba @ 00498bba size=76 sig=undefined FUN_00498bba() cc=unknown
// callers: FUN_0048d7b0,FUN_0049093e
// callees: FUN_00498b98,GlobalLock,FUN_004989b1,GlobalUnlock,FUN_0048f7f1

HGLOBAL FUN_00498bba(HGLOBAL param_1)

{
  int iVar1;
  LPVOID pvVar2;
  LPVOID pvVar3;
  HGLOBAL hMem;
  
  hMem = (HGLOBAL)0x0;
  iVar1 = FUN_004989b1(param_1);
  if (iVar1 != 0) {
    hMem = (HGLOBAL)FUN_00498b98(iVar1);
    if (hMem != (HGLOBAL)0x0) {
      pvVar2 = GlobalLock(hMem);
      pvVar3 = GlobalLock(param_1);
      FUN_0048f7f1(pvVar3,pvVar2,iVar1);
      GlobalUnlock(param_1);
      GlobalUnlock(hMem);
    }
  }
  return hMem;
}

