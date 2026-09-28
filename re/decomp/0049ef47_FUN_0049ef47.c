// FUN_0049ef47 @ 0049ef47 size=65 sig=undefined FUN_0049ef47() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049eb44,FUN_0049d1dd

undefined4
FUN_0049ef47(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar2 = 0;
  if (*(int *)(param_2 + 0x1c) == 6) {
    uVar2 = FUN_0049d1dd(param_1,param_2,param_3,param_4,param_5);
    uVar6 = 0;
    uVar5 = 0;
    uVar4 = 0x32;
    uVar3 = 2;
    uVar1 = FUN_0049ea99(param_2);
    FUN_0049eb44(uVar1,param_2,uVar3,uVar4,uVar5,uVar6);
  }
  return uVar2;
}

