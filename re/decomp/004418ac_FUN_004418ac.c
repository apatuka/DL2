// FUN_004418ac @ 004418ac size=55 sig=undefined FUN_004418ac() cc=unknown
// callers: FUN_00428b74
// callees: FUN_00441388,FUN_004412d4

undefined4 FUN_004418ac(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00441388(param_1,param_2,param_3);
  if ((iVar1 != 0) && (iVar1 = FUN_004412d4(param_1,param_2,param_3), iVar1 == 0)) {
    return 1;
  }
  return 0;
}

