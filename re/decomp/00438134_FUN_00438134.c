// FUN_00438134 @ 00438134 size=221 sig=undefined FUN_00438134() cc=unknown
// callers: 
// callees: FUN_0049eb44,WriteUnitData,FUN_004a2c1b,FUN_00437a18,FUN_0049ea99,FUN_004a43da,FUN_004a1150,FUN_0049eafa

undefined4 FUN_00438134(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (param_2 == 0x2f) {
    if (*(int *)(param_4 + 0x14) == 0x11) {
      FUN_004a43da(param_1,0x2f,param_3,param_4);
      uVar6 = 1;
      uVar4 = 3;
      uVar1 = FUN_0049ea99(param_1);
      uVar1 = FUN_004a1150(uVar1,uVar4,uVar6);
      iVar2 = FUN_0049eafa(uVar1);
      if (iVar2 == 0) {
        uVar7 = 0;
        uVar5 = 1;
        uVar3 = 9;
        uVar6 = 1;
        uVar4 = 3;
        uVar1 = FUN_0049ea99(param_1);
        FUN_0049eb44(uVar1,uVar4,uVar6,uVar3,uVar5,uVar7);
      }
    }
  }
  else if (param_2 == 0x45) {
    uVar6 = 1;
    uVar4 = 3;
    uVar1 = FUN_0049ea99(param_1);
    uVar1 = FUN_004a1150(uVar1,uVar4,uVar6);
    iVar2 = FUN_0049eafa(uVar1);
    if (iVar2 == 1) {
      uVar4 = 3;
      uVar1 = FUN_0049ea99(param_1);
      FUN_004a2c1b(uVar1,uVar4);
      uVar7 = 0;
      uVar5 = 0;
      uVar3 = 9;
      uVar6 = 1;
      uVar4 = 3;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar1,uVar4,uVar6,uVar3,uVar5,uVar7);
    }
  }
  else if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    if (param_4 != 0) {
      FUN_00437a18();
      WriteUnitData();
    }
    return 1;
  }
  uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  return uVar1;
}

