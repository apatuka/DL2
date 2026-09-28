// FUN_004897ea @ 004897ea size=322 sig=undefined FUN_004897ea() cc=unknown
// callers: 
// callees: FUN_00491efa,FUN_0049a93f,FUN_0048c85e,FUN_00491e02,FUN_00491a2b,FUN_0048d32c,FUN_0048f774,FUN_0049a8ed,FUN_0048d2e7,FUN_00492d67,FUN_0049117e,FUN_0049a9e7,FUN_00491ace,FUN_00495c51,FUN_004935fc

undefined4 FUN_004897ea(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int local_44;
  undefined4 local_40 [4];
  undefined4 local_30;
  undefined4 local_24 [4];
  undefined4 local_14 [4];
  
  puVar3 = (undefined4 *)(param_1 + 0x24);
  puVar5 = local_14;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  iVar1 = 0;
  puVar3 = *(undefined4 **)(param_1 + 0x38);
  if (puVar3 != (undefined4 *)0x0) {
    if (((int)puVar3[2] < (int)puVar3[4]) && ((int)puVar3[1] < (int)puVar3[3])) {
      puVar4 = local_14;
      puVar5 = puVar3;
      for (iVar1 = 4; puVar5 = puVar5 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar5;
        puVar4 = puVar4 + 1;
      }
    }
    iVar1 = FUN_0049117e(*(undefined4 *)(param_1 + 0x3c),0xffffffff,puVar3[7]);
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    FUN_0048d2e7(*(undefined4 *)(param_1 + 0x18));
  }
  FUN_0049a8ed();
  FUN_0049a9e7(param_1 + 0x24);
  FUN_004935fc(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),
               *(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x30),0);
  if (iVar1 != 0) {
    FUN_00491a2b(*(undefined4 *)(param_1 + 0x20));
    FUN_00491e02(0x80ffffff);
    FUN_00491efa(0x80000000);
    FUN_0048f774(&local_44,0x20,0);
    puVar3 = local_14;
    puVar5 = local_40;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
    local_30 = 9;
    local_44 = iVar1;
    FUN_00492d67(&local_44);
    FUN_00491ace();
  }
  FUN_0049a93f();
  if (*(int *)(param_1 + 0x18) != 0) {
    FUN_0048d32c();
    if (*(int *)(param_1 + 0x1c) != 0) {
      iVar1 = *(int *)(param_1 + 0x1c);
      puVar3 = (undefined4 *)(param_1 + 0x24);
      puVar5 = local_14;
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = local_14;
      puVar5 = local_24;
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      if ((*(byte *)(param_1 + 0x14) & 2) != 0) {
        FUN_00495c51(local_24,*(undefined4 *)(iVar1 + 4),*(undefined4 *)(iVar1 + 8));
      }
      FUN_0048c85e(*(undefined4 *)(param_1 + 0x18),&DAT_0065e644,local_14,local_24,0,0,0);
    }
  }
  return 1;
}

