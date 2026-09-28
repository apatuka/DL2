// FUN_004644f8 @ 004644f8 size=148 sig=undefined FUN_004644f8() cc=unknown
// callers: FUN_00481540,FUN_00459f18
// callees: FUN_0048d2e7,FUN_00463e88,FUN_0048d32c,FUN_00493784

void FUN_004644f8(int param_1,int param_2,int param_3,int param_4)

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
      if (param_4 == -1) {
        FUN_00493784(param_1,param_2,param_3 + param_1,param_2 + 1,5,0,1);
      }
      else {
        FUN_00463e88(param_1,param_2,param_3,param_4);
      }
    }
    FUN_0048d32c();
  }
  return;
}

