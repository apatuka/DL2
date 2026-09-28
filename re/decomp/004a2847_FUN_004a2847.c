// FUN_004a2847 @ 004a2847 size=283 sig=undefined FUN_004a2847() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049c3c9,FUN_0049eb44,FUN_0049ea99,FUN_0049f696,FUN_0048ddd1,FUN_0049cc43,FUN_0049e3d7

void FUN_004a2847(int param_1,int *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (*(int *)(param_1 + 0x1c) == 5) {
    FUN_0049e3d7(param_1,param_2);
    if ((*(byte *)(param_2 + 5) & 0x20) == 0) {
      FUN_0049f696(param_1);
    }
  }
  else if (*(int *)(param_1 + 0x1c) == 9) {
    if ((*(byte *)(param_2 + 5) & 0x20) == 0) {
      FUN_0049f696(param_1);
    }
    if (param_2[2] == 3) {
      iVar4 = param_2[1] - param_2[4];
      iVar3 = *param_2 - param_2[3];
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049c3c9(uVar1,param_1,iVar3,iVar4);
    }
    else if (((*(byte *)(param_1 + 0x27) & 0x20) == 0) || ((param_2[2] != 5 && (param_2[2] != 6))))
    {
      if ((*(byte *)(param_2 + 5) & 0x20) == 0) {
        iVar3 = FUN_0048ddd1();
        if (*(int *)(param_1 + 0x58) == 0) {
          iVar4 = 10;
        }
        else {
          iVar4 = *(int *)(param_1 + 0x58);
        }
        *(int *)(param_1 + 0x5c) = iVar3 + iVar4 * 2;
        FUN_0049cc43(param_1,param_2[2],param_2[5]);
      }
      else {
        uVar2 = FUN_0048ddd1();
        if (*(uint *)(param_1 + 0x5c) <= uVar2) {
          iVar3 = FUN_0048ddd1();
          if (*(int *)(param_1 + 0x58) == 0) {
            iVar4 = 10;
          }
          else {
            iVar4 = *(int *)(param_1 + 0x58);
          }
          *(int *)(param_1 + 0x5c) = iVar3 + iVar4;
          FUN_0049cc43(param_1,param_2[2],param_2[5]);
        }
      }
    }
    else {
      iVar3 = param_2[1];
      iVar4 = *param_2;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049c3c9(uVar1,param_1,iVar4,iVar3);
    }
  }
  else if ((*(byte *)(param_2 + 5) & 0x20) == 0) {
    uVar7 = 0;
    uVar6 = 0x2f;
    uVar5 = 2;
    iVar3 = param_1;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar1,iVar3,uVar5,uVar6,uVar7,param_2);
    FUN_0049f696(param_1);
  }
  return;
}

