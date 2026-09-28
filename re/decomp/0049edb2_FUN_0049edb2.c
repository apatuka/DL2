// FUN_0049edb2 @ 0049edb2 size=148 sig=undefined FUN_0049edb2() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049d5e9,FUN_0049df38

undefined4 FUN_0049edb2(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  if (*(int *)(param_1 + 0x1c) == 5) {
    if (param_2 == 0x1c) {
      uVar3 = param_4 >> 0x10;
      param_4 = param_4 & 0xffff;
      uVar2 = FUN_0049ea99(param_1);
      uVar2 = FUN_0049df38(uVar2,param_1,param_4,uVar3,param_3);
      return uVar2;
    }
  }
  else if (*(int *)(param_1 + 0x1c) == 6) {
    if (param_2 == 0x1b) {
      uVar4 = 5;
      uVar2 = param_3;
      uVar1 = FUN_0049ea99(param_1);
      uVar2 = FUN_0049d5e9(uVar1,param_1,param_3,uVar2,uVar4);
      return uVar2;
    }
    if (param_2 == 0x1c) {
      uVar3 = param_4 >> 0x10;
      param_4 = param_4 & 0xffff;
      uVar2 = FUN_0049ea99(param_1);
      uVar2 = FUN_0049d5e9(uVar2,param_1,param_4,uVar3,param_3);
      return uVar2;
    }
  }
  return 0;
}

