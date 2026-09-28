// FUN_00494aa7 @ 00494aa7 size=95 sig=undefined FUN_00494aa7() cc=unknown
// callers: FUN_00415208
// callees: FUN_00496cc3

void FUN_00494aa7(int *param_1)

{
  if (DAT_0065ecb0 == 0) {
    param_1[3] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    *param_1 = 0;
  }
  else {
    FUN_00496cc3(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,param_1);
    param_1[1] = param_1[1] + DAT_0065ec88;
    param_1[3] = param_1[3] + DAT_0065ec88;
    *param_1 = *param_1 + DAT_0065ec84;
    param_1[2] = param_1[2] + DAT_0065ec84;
  }
  return;
}

