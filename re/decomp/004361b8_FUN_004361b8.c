// FUN_004361b8 @ 004361b8 size=251 sig=undefined FUN_004361b8() cc=unknown
// callers: FUN_004363f8
// callees: FUN_0049eb44,FUN_004a2004,FUN_004a3de6,FUN_00414f04,FUN_004493dc
// strings: \"New Player\"

undefined4 FUN_004361b8(void)

{
  DAT_004c465c = FUN_004a3de6(0,0x37303044);
  if (DAT_004c465c != 0) {
    FUN_004493dc(1);
    DAT_00558eac = DAT_004d59b4;
    DAT_004d59b4 = 0x29;
    FUN_00414f04(DAT_004c465c);
    FUN_004a2004(DAT_004c465c);
    FUN_0049eb44(DAT_004c465c,3,1,0xf,0,s_New_Player_00509804);
    FUN_0049eb44(DAT_004c465c,3,1,0x1c,4,0);
    if (DAT_004d59ac == 0) {
      FUN_0049eb44(DAT_004c465c,4,1,10,1,0);
      FUN_0049eb44(DAT_004c465c,6,1,10,1,0);
      FUN_0049eb44(DAT_004c465c,7,1,10,1,0);
      FUN_0049eb44(DAT_004c465c,0xb,1,10,1,0);
      FUN_0049eb44(DAT_004c465c,10,1,10,1,0);
    }
    return 1;
  }
  return 0;
}

