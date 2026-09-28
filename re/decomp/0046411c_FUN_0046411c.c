// FUN_0046411c @ 0046411c size=568 sig=undefined FUN_0046411c() cc=unknown
// callers: FUN_00463f38,FUN_00481da0,CreateWinGWindow
// callees: FUN_0048d2e7,FUN_00463e88,FUN_0048d32c,FUN_00493784,FUN_00463ee0

void FUN_0046411c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  undefined4 local_1c;
  undefined4 local_18;
  
  FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
  bVar1 = param_1 < DAT_0058df34;
  if (bVar1) {
    param_3 = param_3 - (DAT_0058df34 - param_1);
    param_1 = DAT_0058df34;
  }
  bVar2 = param_2 < DAT_0058df38;
  if (bVar2) {
    param_4 = param_4 - (DAT_0058df38 - param_2);
    param_2 = DAT_0058df38;
  }
  bVar3 = DAT_0058df3c < param_3 + param_1;
  if (bVar3) {
    param_3 = DAT_0058df3c - param_1;
  }
  bVar4 = DAT_0058df40 < param_4 + param_2;
  if (bVar4) {
    param_4 = DAT_0058df40 - param_2;
  }
  if ((0 < param_4) && (0 < param_3)) {
    if (param_6 == 0) {
      if (!bVar1) {
        FUN_00463ee0(param_1,param_2,param_4,param_5);
      }
      if (!bVar3) {
        FUN_00463ee0(param_3 + -1 + param_1,param_2,param_4,param_5);
      }
      if (!bVar2) {
        FUN_00463e88(param_1,param_2,param_3,param_5);
      }
      if (!bVar4) {
        FUN_00463e88(param_1,param_2 + param_4 + -1,param_3,param_5);
      }
    }
    else if (param_6 == 1) {
      if (!bVar1) {
        FUN_00493784(param_1,param_2,param_1 + 1,param_4 + param_2,0xffffffff,0,4);
      }
      if (!bVar3) {
        FUN_00493784(param_3 + param_1 + -1,param_2,param_3 + param_1,param_4 + param_2,0xffffffff,0
                     ,4);
      }
      if (!bVar2) {
        FUN_00493784(param_1,param_2,param_3 + param_1,param_2 + 1,0xffffffff,0,4);
      }
      if (!bVar4) {
        FUN_00493784(param_1,param_4 + param_2 + -1,param_3 + param_1,param_4 + param_2,0xffffffff,0
                     ,4);
      }
    }
    else if (param_6 == 2) {
      if (param_5 == 0) {
        local_18 = 0xff;
        local_1c = 0;
      }
      else {
        local_18 = 0;
        local_1c = 0xff;
      }
      if (!bVar1) {
        FUN_00463ee0(param_1,param_2,param_4,local_18);
      }
      if (!bVar3) {
        FUN_00463ee0(param_3 + -1 + param_1,param_2,param_4,local_1c);
      }
      if (!bVar2) {
        FUN_00463e88(param_1,param_2,param_3,local_18);
      }
      if (!bVar4) {
        FUN_00463e88(param_1,param_2 + param_4 + -1,param_3,local_1c);
      }
    }
  }
  FUN_0048d32c();
  return;
}

