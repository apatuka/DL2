// FUN_00482cec @ 00482cec size=80 sig=undefined FUN_00482cec() cc=unknown
// callers: FUN_0041ccb0,FUN_00482a38,FUN_00487a00
// callees: FUN_0048a4d2,FUN_0048a3ef,FUN_00482b04

void FUN_00482cec(void)

{
  if ((DAT_00657e20 != 0) && (DAT_00657e30 != -1)) {
    FUN_00482b04();
    DAT_00657e38 = DAT_00657e30;
    FUN_0048a4d2(DAT_00657e34,&DAT_00657e3c);
    FUN_0048a3ef(DAT_00657e34);
    DAT_00657e34 = 0;
    DAT_00657e30 = -1;
  }
  return;
}

