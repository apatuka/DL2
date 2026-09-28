// FUN_00445ae4 @ 00445ae4 size=175 sig=undefined FUN_00445ae4() cc=unknown
// callers: 
// callees: FUN_00445b94,DeleteUnit,FUN_0045951c,RemoveArmyFromTaskForce,FUN_004594b8

void FUN_00445ae4(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_60;
  undefined1 local_59;
  
  iVar1 = FUN_00445b94(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x76);
    puVar4 = &DAT_004c5178;
    puVar5 = &local_60;
    for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_59 = (&DAT_004faf87)[param_2 * 0x24];
    if (*(char *)(param_1 + 0x21) == '\0') {
      iVar3 = FUN_004594b8(&local_60);
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
        iVar2 = FUN_004594b8(iVar1);
        if (iVar3 == iVar2) {
          RemoveArmyFromTaskForce(iVar1);
          DeleteUnit(iVar1);
          return;
        }
      }
    }
    else {
      iVar3 = FUN_0045951c(&local_60);
      for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
        iVar2 = FUN_0045951c(iVar1);
        if (iVar3 == iVar2) {
          RemoveArmyFromTaskForce(iVar1);
          DeleteUnit(iVar1);
          return;
        }
      }
    }
  }
  return;
}

