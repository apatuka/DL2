// FUN_00498c06 @ 00498c06 size=56 sig=undefined FUN_00498c06() cc=unknown
// callers: FUN_0049b22d
// callees: FUN_00498b98,GlobalLock,GlobalUnlock,FUN_0048f7f1

HGLOBAL FUN_00498c06(undefined4 param_1,int param_2)

{
  LPVOID pvVar1;
  HGLOBAL hMem;
  
  hMem = (HGLOBAL)0x0;
  if (param_2 != 0) {
    hMem = (HGLOBAL)FUN_00498b98(param_2);
    if (hMem != (HGLOBAL)0x0) {
      pvVar1 = GlobalLock(hMem);
      FUN_0048f7f1(param_1,pvVar1,param_2);
      GlobalUnlock(hMem);
    }
  }
  return hMem;
}

