// FUN_0048baf6 @ 0048baf6 size=39 sig=undefined FUN_0048baf6() cc=unknown
// callers: FUN_0048bb1d
// callees: GlobalAlloc

HGLOBAL FUN_0048baf6(uint param_1)

{
  HGLOBAL pvVar1;
  
  if ((param_1 == 0) || ((param_1 & 0x80000000) != 0)) {
    pvVar1 = (HGLOBAL)0x0;
  }
  else {
    pvVar1 = GlobalAlloc(0,param_1 + 3 & 0xfffffffc);
  }
  return pvVar1;
}

