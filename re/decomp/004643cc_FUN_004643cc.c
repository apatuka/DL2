// FUN_004643cc @ 004643cc size=120 sig=undefined FUN_004643cc() cc=unknown
// callers: FUN_00463f38
// callees: FUN_0048d2e7,FUN_0048d32c,FUN_00463ee0

void FUN_004643cc(int param_1,int param_2,int param_3,undefined4 param_4)

{
  if ((DAT_0058df34 <= param_1) && (param_1 < DAT_0058df3c)) {
    if (param_2 < DAT_0058df38) {
      param_3 = param_3 - (DAT_0058df38 - param_2);
      param_2 = DAT_0058df38;
    }
    if (DAT_0058df40 < param_3 + param_2) {
      param_3 = DAT_0058df40 - param_2;
    }
    FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
    if (0 < param_3) {
      FUN_00463ee0(param_1,param_2,param_3,param_4);
    }
    FUN_0048d32c();
  }
  return;
}

