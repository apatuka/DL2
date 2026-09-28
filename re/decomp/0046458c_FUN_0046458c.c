// FUN_0046458c @ 0046458c size=148 sig=undefined FUN_0046458c() cc=unknown
// callers: FUN_00481540,FUN_00459f18
// callees: FUN_0048d2e7,FUN_0048d32c,FUN_00493784,FUN_00463ee0

void FUN_0046458c(int param_1,int param_2,int param_3,int param_4)

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
      if (param_4 == -1) {
        FUN_00493784(param_1,param_2,param_1 + 1,param_3 + param_2,5,0,1);
      }
      else {
        FUN_00463ee0(param_1,param_2,param_3,param_4);
      }
    }
    FUN_0048d32c();
  }
  return;
}

