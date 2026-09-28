// FUN_0048e169 @ 0048e169 size=108 sig=undefined FUN_0048e169() cc=unknown
// callers: CheckSubRes,FUN_0049ea6a,FUN_004a2cb5,FUN_00431128,FUN_00427440,FUN_00425268
// callees: FUN_0048dc0d,FUN_0048e138,FUN_0048dcbb

undefined4 FUN_0048e169(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  FUN_0048dc0d();
  if (((param_1 & 1) != 0) && (iVar1 = FUN_0048dcbb(0x201,param_2,param_3,param_4,1), iVar1 != 0)) {
    return 1;
  }
  if (((param_1 & 2) != 0) && (iVar1 = FUN_0048dcbb(0x204,param_2,param_3,param_4,1), iVar1 != 0)) {
    return 2;
  }
  FUN_0048e138(param_2,param_3);
  return 0;
}

