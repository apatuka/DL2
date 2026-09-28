// FUN_0041e6d4 @ 0041e6d4 size=278 sig=undefined FUN_0041e6d4() cc=unknown
// callers: FUN_004618e8,FUN_004634a0
// callees: FUN_00414f04,FUN_0042e584,FUN_004493dc,FUN_004a3de6,FUN_004a60b1,FUN_004a2004,FUN_0049eb44

undefined4 FUN_0041e6d4(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b792c = FUN_004a3de6(0,0x32313044);
  if (DAT_004b792c == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_0053b87c = DAT_004d59b4;
    DAT_004d59b4 = 0x49;
    FUN_00414f04(DAT_004b792c);
    local_10 = DAT_004b7934;
    local_c = DAT_004b7930;
    local_8 = DAT_004b793c;
    local_4 = DAT_004b7938;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b792c);
    FUN_0049eb44(DAT_004b792c,1,1,7,0,FUN_0041e4d0);
    if (DAT_0058f1fc != 0) {
      FUN_0049eb44(DAT_004b792c,3,1,10,1,0);
    }
    FUN_0049eb44(DAT_004b792c,5,1,10,1,0);
    if (DAT_004d513c == 0) {
      FUN_0042e584((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8]);
    }
    else {
      FUN_0042e584(DAT_004c3664);
    }
    uVar1 = 1;
  }
  return uVar1;
}

