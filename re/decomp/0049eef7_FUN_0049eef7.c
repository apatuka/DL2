// FUN_0049eef7 @ 0049eef7 size=80 sig=undefined FUN_0049eef7() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049eb44,FUN_0049d18d

undefined4 FUN_0049eef7(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  uVar2 = 0;
  if (*(int *)(param_2 + 0x1c) == 6) {
    uVar2 = FUN_0049d18d(param_1,param_2,param_3);
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    iVar3 = param_2;
    uVar1 = FUN_0049ea99(param_2);
    FUN_0049eb44(uVar1,iVar3,uVar4,uVar5,uVar6,uVar7);
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 0x32;
    uVar4 = 2;
    uVar1 = FUN_0049ea99(param_2);
    FUN_0049eb44(uVar1,param_2,uVar4,uVar5,uVar6,uVar7);
  }
  return uVar2;
}

