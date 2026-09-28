// FUN_004a2962 @ 004a2962 size=105 sig=undefined FUN_004a2962() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049eb44,FUN_0049ea99,FUN_0049c244

void FUN_004a2962(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(param_1 + 0x1c) == 9) {
    if ((param_4 == 3) ||
       (((*(byte *)(param_1 + 0x27) & 0x20) != 0 && ((param_4 == 5 || (param_4 == 6)))))) {
      uVar5 = 0;
      iVar3 = param_1;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049c244(uVar1,iVar3,uVar5);
      uVar6 = 0;
      uVar4 = 0;
      uVar2 = 8;
      uVar5 = 2;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar1,param_1,uVar5,uVar2,uVar4,uVar6);
    }
  }
  else {
    uVar2 = 0x45;
    uVar5 = 2;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar1,param_1,uVar5,uVar2,param_4,param_7);
  }
  return;
}

