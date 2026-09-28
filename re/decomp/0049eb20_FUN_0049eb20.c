// FUN_0049eb20 @ 0049eb20 size=36 sig=undefined FUN_0049eb20() cc=unknown
// callers: FUN_0049f83e,FUN_0049f7c9,FUN_0049f7f8
// callees: FUN_004a60b1

void FUN_0049eb20(int param_1,undefined4 param_2)

{
  if (*(int *)(param_1 + 0x60) == 0) {
    FUN_004a60b1(param_2,0);
  }
  else {
    (**(code **)(param_1 + 0x60))(param_1,param_2,0);
  }
  return;
}

