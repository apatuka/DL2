// FUN_004899fd @ 004899fd size=31 sig=undefined FUN_004899fd() cc=unknown
// callers: FUN_00489ae1
// callees: FUN_004989cf

undefined4 FUN_004899fd(int param_1)

{
  if (param_1 != 0) {
    (**(code **)(param_1 + 0x5c))(param_1);
    FUN_004989cf(param_1);
  }
  return 1;
}

