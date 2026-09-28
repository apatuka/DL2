// FUN_004877c8 @ 004877c8 size=88 sig=undefined FUN_004877c8() cc=unknown
// callers: FUN_00487a00,FUN_00487e34
// callees: FUN_0049a8ed,FUN_0049a93f,FUN_0048d2e7,FUN_0048d32c,FUN_0049a9e7,FUN_004935fc

void FUN_004877c8(int param_1,undefined4 param_2)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0048d2e7(param_1);
  FUN_0049a8ed();
  local_14 = 0;
  local_10 = 0;
  local_c = *(undefined4 *)(param_1 + 4);
  local_8 = *(undefined4 *)(param_1 + 8);
  FUN_0049a9e7(&local_14);
  FUN_004935fc(0,0,*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8),param_2);
  FUN_0049a93f();
  FUN_0048d32c();
  return;
}

