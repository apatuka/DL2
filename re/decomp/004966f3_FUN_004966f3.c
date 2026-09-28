// FUN_004966f3 @ 004966f3 size=52 sig=undefined FUN_004966f3() cc=unknown
// callers: FUN_00496727
// callees: FUN_00496945,FUN_0049659f

undefined4 FUN_004966f3(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00496945(param_1,param_2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (*(int *)(iVar1 + 8) == 0) {
      FUN_0049659f(param_1,param_2);
    }
    uVar2 = *(undefined4 *)(iVar1 + 8);
  }
  return uVar2;
}

