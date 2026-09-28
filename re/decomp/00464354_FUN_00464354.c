// FUN_00464354 @ 00464354 size=120 sig=undefined FUN_00464354() cc=unknown
// callers: FUN_00463f38
// callees: FUN_0048d2e7,FUN_00463e88,FUN_0048d32c

void FUN_00464354(int param_1,int param_2,int param_3,undefined4 param_4)

{
  if ((DAT_0058df38 <= param_2) && (param_2 < DAT_0058df40)) {
    if (param_1 < DAT_0058df34) {
      param_3 = param_3 - (DAT_0058df34 - param_1);
      param_1 = DAT_0058df34;
    }
    if (DAT_0058df3c < param_3 + param_1) {
      param_3 = DAT_0058df3c - param_1;
    }
    FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
    if (0 < param_3) {
      FUN_00463e88(param_1,param_2,param_3,param_4);
    }
    FUN_0048d32c();
  }
  return;
}

