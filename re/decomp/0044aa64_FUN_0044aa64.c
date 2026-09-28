// FUN_0044aa64 @ 0044aa64 size=94 sig=undefined FUN_0044aa64() cc=unknown
// callers: FUN_0044ad14
// callees: FUN_0041e440,FUN_004217a0

void FUN_0044aa64(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  if (DAT_004c5bc8 != '\0') {
    if (DAT_004d59b4 == 5) {
      FUN_0041e440(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if (DAT_004d59b4 == 7) {
      FUN_004217a0(param_1,param_2,param_3,param_4,param_5,param_6);
    }
  }
  DAT_004c5bc8 = 0;
  return;
}

