// FUN_004a2be7 @ 004a2be7 size=52 sig=undefined FUN_004a2be7() cc=unknown
// callers: FUN_004a2cb5,FUN_004a2ac6
// callees: FUN_004a2ac6

void FUN_004a2be7(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  if (*(int *)(param_1 + 0x58) == 0) {
    FUN_004a2ac6(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    (**(code **)(param_1 + 0x58))(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}

