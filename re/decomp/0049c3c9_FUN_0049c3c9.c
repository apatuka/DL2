// FUN_0049c3c9 @ 0049c3c9 size=148 sig=undefined FUN_0049c3c9() cc=unknown
// callers: FUN_004a2847,FUN_004a29cb
// callees: FUN_0049c244,FUN_0049eb44,FUN_0049c14c,FUN_0049ea99,FUN_0049c313

void FUN_0049c3c9(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  iVar1 = FUN_0049c14c(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    iVar2 = *(int *)(param_1 + 0x98);
  }
  else {
    iVar2 = FUN_0049c313(param_1,param_2);
  }
  if (iVar2 != *(int *)(param_2 + 0x48)) {
    uVar7 = *(undefined4 *)(param_2 + 0x48);
    *(int *)(param_2 + 0x48) = iVar2;
    uVar6 = 0;
    uVar5 = 0x2e;
    uVar4 = 2;
    iVar2 = param_2;
    uVar3 = FUN_0049ea99(param_2);
    iVar2 = FUN_0049eb44(uVar3,iVar2,uVar4,uVar5,uVar6,uVar7);
    if (iVar2 != 0) {
      if (*(int *)(param_2 + 0x48) < *(int *)(param_2 + 0xe8)) {
        *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_2 + 0xe8);
      }
      else if (*(int *)(param_2 + 0xec) < *(int *)(param_2 + 0x48)) {
        *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_2 + 0xec);
      }
    }
  }
  if (iVar1 == 0) {
    FUN_0049c244(param_1,param_2,1);
  }
  return;
}

