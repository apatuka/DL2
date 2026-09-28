// FUN_00412d38 @ 00412d38 size=89 sig=undefined FUN_00412d38() cc=unknown
// callers: CheckEventLog,CheckSubRes,FUN_00431258,CheckSubTech,CheckSubUnit,FUN_00424e28,FUN_00425268,FUN_00412d94,FUN_00425d68,FUN_0041edd8,FUN_0041f2c8,FUN_00422344,FUN_0042cfbc,FUN_0042d304,CheckSubInfo,FUN_0042623c
// callees: FUN_00413348

undefined4 FUN_00412d38(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0xe) == 0) || (*(char *)(param_1 + 0x3c) != '\0')) {
    uVar1 = 0xffffffff;
  }
  else {
    if (param_2 == 0) {
      FUN_00413348(*(undefined4 *)(*(int *)(param_1 + 0xe) + -4 + *(int *)(param_1 + 10) * 4),
                   *(undefined4 *)(param_1 + 0x1e),*(undefined4 *)(param_1 + 0x22),
                   *(undefined4 *)(param_1 + 0x26));
    }
    else {
      FUN_00413348(*(undefined4 *)(*(int *)(param_1 + 0xe) + -4 + *(int *)(param_1 + 10) * 4),
                   param_2,*(undefined4 *)(param_1 + 0x22),*(undefined4 *)(param_1 + 0x26));
    }
    uVar1 = 0;
  }
  return uVar1;
}

