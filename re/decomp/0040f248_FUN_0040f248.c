// FUN_0040f248 @ 0040f248 size=90 sig=undefined FUN_0040f248() cc=unknown
// callers: FUN_0040f2e0
// callees: FUN_0040f154,RemoveArmyFromTaskForce,FUN_00401ac0

void FUN_0040f248(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  do {
    iVar1 = *piVar3;
    if ((iVar1 != 0) && ((&DAT_004faf87)[*(char *)(iVar1 + 6) * 0x24] != '\t')) {
      iVar2 = FUN_0040f154(iVar1,*(undefined4 *)(param_1 + 0x10));
      if (iVar2 == 0) {
        RemoveArmyFromTaskForce(iVar1);
      }
      else {
        FUN_00401ac0(iVar1,iVar2,0);
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 0x10);
  return;
}

