// FUN_0048fc05 @ 0048fc05 size=190 sig=undefined FUN_0048fc05() cc=unknown
// callers: 
// callees: FUN_0048fade,FUN_00498b98,GlobalUnlock,FUN_0048fbbf,FUN_0048f992,FUN_0048f8e8,GlobalLock

HGLOBAL FUN_0048fc05(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  HGLOBAL hMem;
  
  hMem = (HGLOBAL)0x0;
  iVar1 = FUN_0048f8e8(param_1,param_2);
  if (iVar1 == 0) {
    hMem = (HGLOBAL)0x0;
  }
  else {
    if (param_3 == 0) {
      if ((param_2 != 1) && (param_2 != 2)) {
        FUN_0048fbbf(iVar1,0);
        return (HGLOBAL)0x0;
      }
      param_3 = FUN_0048fade(iVar1,0,2);
      FUN_0048fade(iVar1,0,0);
    }
    if (param_3 != 0) {
      iVar2 = 2;
      if (param_4 == 0) {
        iVar2 = 0;
      }
      hMem = (HGLOBAL)FUN_00498b98(iVar2 + param_3);
      if (hMem != (HGLOBAL)0x0) {
        puVar3 = GlobalLock(hMem);
        iVar2 = 2;
        if (param_4 == 0) {
          iVar2 = 0;
        }
        FUN_0048f992(iVar1,iVar2 + (int)puVar3,param_3);
        if (param_4 != 0) {
          *puVar3 = 1;
        }
        GlobalUnlock(hMem);
      }
    }
    FUN_0048fbbf(iVar1,0);
  }
  return hMem;
}

