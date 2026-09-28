// FUN_00464620 @ 00464620 size=384 sig=undefined FUN_00464620() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c,FUN_004442dc,FUN_0048180c
// callees: FUN_0049b3c9,FUN_0048d2e7,FUN_0048d32c,FUN_004935fc,FUN_00493784

undefined4 FUN_00464620(int param_1,int param_2,int param_3,int param_4,uint param_5,int param_6)

{
  if (param_2 < DAT_0058df38) {
    param_4 = param_4 - (DAT_0058df38 - param_2);
    param_2 = DAT_0058df38;
  }
  if (param_1 < DAT_0058df34) {
    param_3 = param_3 - (DAT_0058df34 - param_1);
    param_1 = DAT_0058df34;
  }
  if ((((param_1 < DAT_0058df3c) && (param_2 < DAT_0058df40)) && (0 < param_3)) && (0 < param_4)) {
    if (DAT_0058df3c < param_3 + param_1) {
      param_3 = DAT_0058df3c - param_1;
    }
    if (DAT_0058df40 < param_4 + param_2) {
      param_4 = DAT_0058df40 - param_2;
    }
    if ((-1 < param_3) && (-1 < param_4)) {
      if (param_6 == 0) {
        FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
        if ((int)param_5 < 0) {
          FUN_00493784(param_1,param_2,param_3 + param_1,param_4 + param_2,-param_5,0,1);
        }
        else {
          FUN_00493784(param_1,param_2,param_3 + param_1,param_4 + param_2,param_5,0,2);
        }
        FUN_0048d32c();
      }
      else if (param_6 == 1) {
        FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
        if (*(int *)(DAT_0051bddc + 0xc) == 8) {
          FUN_004935fc(param_1,param_2,param_3 + param_1,param_4 + param_2,param_5);
        }
        else {
          if ((param_5 & 0x80000000) == 0) {
            param_5 = FUN_0049b3c9(DAT_0058df44,param_5);
          }
          FUN_004935fc(param_1,param_2,param_3 + param_1,param_4 + param_2,param_5);
        }
        FUN_0048d32c();
      }
      return 1;
    }
  }
  return 0;
}

