// FUN_004727dc @ 004727dc size=45 sig=undefined FUN_004727dc() cc=unknown
// callers: FUN_004371e4,FUN_0043793c,FUN_004723cc,FUN_00472448,FUN_00484980,FUN_0045ca3c,FUN_00407c2c,FUN_00407864
// callees: FUN_00472730,FUN_004726cc

undefined4 FUN_004727dc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = (int)*(char *)(param_1 + 0x20);
  if (iVar1 != -1) {
    uVar2 = FUN_004726cc(param_1,param_2,iVar1);
    uVar2 = FUN_00472730(uVar2,iVar1);
  }
  return uVar2;
}

