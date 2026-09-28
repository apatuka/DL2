// FUN_0048d76a @ 0048d76a size=70 sig=undefined FUN_0048d76a() cc=unknown
// callers: FUN_004995ab,FUN_00498196,FUN_0048d7da,FUN_0048d8a1,FUN_00411808,FUN_004916e9,FUN_00499227,FUN_004a52db
// callees: GlobalLock,FUN_0048d713,GlobalUnlock,FUN_00498b98,FUN_0048d740

HGLOBAL FUN_0048d76a(int param_1,undefined4 param_2)

{
  HGLOBAL hMem;
  LPVOID pvVar1;
  
  hMem = (HGLOBAL)FUN_00498b98(param_1 * 4 + 8);
  if (hMem != (HGLOBAL)0x0) {
    pvVar1 = GlobalLock(hMem);
    FUN_0048d740(pvVar1,param_1,param_2);
    FUN_0048d713(pvVar1,0);
    GlobalUnlock(hMem);
  }
  return hMem;
}

