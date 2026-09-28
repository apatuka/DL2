// FUN_0048e319 @ 0048e319 size=108 sig=undefined FUN_0048e319() cc=unknown
// callers: FUN_004a2cb5,FUN_00427440
// callees: FUN_0048dc0d,FUN_0048e138,FUN_0048dcbb

undefined4 FUN_0048e319(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  FUN_0048dc0d();
  if (((param_1 & 1) != 0) && (iVar1 = FUN_0048dcbb(0x203,param_2,param_3,param_4,1), iVar1 != 0)) {
    return 1;
  }
  if (((param_1 & 2) != 0) && (iVar1 = FUN_0048dcbb(0x206,param_2,param_3,param_4,1), iVar1 != 0)) {
    return 2;
  }
  FUN_0048e138(param_2,param_3);
  return 0;
}

