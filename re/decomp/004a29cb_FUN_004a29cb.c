// FUN_004a29cb @ 004a29cb size=92 sig=undefined FUN_004a29cb() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049c3c9,FUN_0049ea99

void FUN_004a29cb(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x1c) == 9) {
    if (param_4 == 3) {
      param_3 = param_3 - param_6;
      param_2 = param_2 - param_5;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049c3c9(uVar1,param_1,param_2,param_3);
    }
    else if (((*(byte *)(param_1 + 0x27) & 0x20) != 0) && ((param_4 == 5 || (param_4 == 6)))) {
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049c3c9(uVar1,param_1,param_2,param_3);
    }
  }
  return;
}

