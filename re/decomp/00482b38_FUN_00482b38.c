// FUN_00482b38 @ 00482b38 size=101 sig=undefined FUN_00482b38() cc=unknown
// callers: WinMain,FUN_0041ccb0,FUN_0043df90,FUN_0043e024
// callees: FUN_00482ce4,FUN_00482ba0,FUN_00482c8c

void FUN_00482b38(int param_1,undefined4 param_2)

{
  undefined4 unaff_ESI;
  
  if (DAT_00657e20 != 0) {
    FUN_00482ce4();
    DAT_00657e2c = param_1;
    if (param_1 == 1) {
      DAT_00657e30 = 0x35313053;
    }
    else if (param_1 - 2U < 2) {
      DAT_00657e30 = FUN_00482c8c();
    }
    else {
      DAT_00657e30 = param_2;
      if (param_1 - 2U != 2) {
        DAT_00657e30 = unaff_ESI;
      }
    }
    if (param_1 != 0) {
      DAT_00657e34 = FUN_00482ba0(DAT_00657e30,1,0,1,0,1,0);
    }
  }
  return;
}

