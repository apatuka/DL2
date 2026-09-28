// FUN_00425bc4 @ 00425bc4 size=418 sig=undefined FUN_00425bc4() cc=unknown
// callers: 
// callees: FUN_0049eafa,FUN_004256f4,FUN_00425ef8,FUN_0049ea99,FUN_004a1150,FUN_004257f0,FUN_004a43da,FUN_00425ac4,FUN_0049eb44,FUN_004a2c1b,FUN_00425f04

void FUN_00425bc4(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  if (DAT_004b7d08 == 0) {
    if (param_2 == 0x2f) {
      if (*(int *)(param_4 + 0x14) == 0x11) {
        FUN_004a43da(param_1,0x2f,param_3,param_4);
        uVar7 = 1;
        uVar5 = 7;
        uVar1 = FUN_0049ea99(param_1);
        uVar1 = FUN_004a1150(uVar1,uVar5,uVar7);
        iVar2 = FUN_0049eafa(uVar1);
        if (iVar2 == 0) {
          uVar8 = 0;
          uVar6 = 1;
          uVar4 = 9;
          uVar7 = 1;
          uVar5 = 7;
          uVar1 = FUN_0049ea99(param_1);
          FUN_0049eb44(uVar1,uVar5,uVar7,uVar4,uVar6,uVar8);
        }
      }
    }
    else if (param_2 == 0x45) {
      uVar7 = 1;
      uVar5 = 7;
      uVar1 = FUN_0049ea99(param_1);
      uVar1 = FUN_004a1150(uVar1,uVar5,uVar7);
      iVar2 = FUN_0049eafa(uVar1);
      if (iVar2 == 1) {
        uVar5 = 7;
        uVar1 = FUN_0049ea99(param_1);
        FUN_004a2c1b(uVar1,uVar5);
        uVar8 = 0;
        uVar6 = 0;
        uVar4 = 9;
        uVar7 = 1;
        uVar5 = 7;
        uVar1 = FUN_0049ea99(param_1);
        FUN_0049eb44(uVar1,uVar5,uVar7,uVar4,uVar6,uVar8);
      }
    }
    else if (param_2 == 0x3b) {
      uVar8 = 0;
      uVar6 = 0;
      uVar4 = 0x18;
      uVar7 = 2;
      uVar1 = param_1;
      uVar5 = FUN_0049ea99(param_1);
      iVar2 = FUN_0049eb44(uVar5,uVar1,uVar7,uVar4,uVar6,uVar8);
      uVar8 = 0;
      uVar6 = 0;
      uVar4 = 0x22;
      uVar7 = 2;
      uVar1 = param_1;
      uVar5 = FUN_0049ea99(param_1);
      iVar3 = FUN_0049eb44(uVar5,uVar1,uVar7,uVar4,uVar6,uVar8);
      if (iVar3 < iVar2) {
        FUN_004256f4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar3 * 0x24);
        FUN_004257f0(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar3 * 0x24);
        FUN_00425ac4(*(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar3 * 0x24);
        DAT_00557554 = *(int *)(*(int *)(DAT_00557554 + 0x1a) + 0x16) + iVar3 * 0x24;
        FUN_00425f04();
        FUN_00425ef8();
      }
    }
    FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  else {
    FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return;
}

