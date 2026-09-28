// FUN_0049f696 @ 0049f696 size=127 sig=undefined FUN_0049f696() cc=unknown
// callers: FUN_004a2ac6,FUN_004a2847,FUN_004a2cb5
// callees: FUN_0049ea99,FUN_0049eb44

void FUN_0049f696(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if ((((param_1 != 0) && (iVar1 = FUN_0049ea99(param_1), iVar1 != 0)) &&
      (*(int *)(iVar1 + 300) != 0)) && (**(int **)(iVar1 + 300) != 0)) {
    for (iVar1 = **(int **)(iVar1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (param_1 == iVar1) {
        if ((*(byte *)(iVar1 + 0x2a) & 0x80) == 0) {
          uVar7 = 0;
          uVar6 = 1;
          uVar5 = 0x34;
          uVar4 = 2;
          iVar3 = iVar1;
          uVar2 = FUN_0049ea99(iVar1);
          FUN_0049eb44(uVar2,iVar3,uVar4,uVar5,uVar6,uVar7);
        }
      }
      else if ((*(byte *)(iVar1 + 0x2a) & 0x80) != 0) {
        uVar7 = 0;
        uVar6 = 0;
        uVar5 = 0x34;
        uVar4 = 2;
        iVar3 = iVar1;
        uVar2 = FUN_0049ea99(iVar1);
        FUN_0049eb44(uVar2,iVar3,uVar4,uVar5,uVar6,uVar7);
      }
    }
  }
  return;
}

