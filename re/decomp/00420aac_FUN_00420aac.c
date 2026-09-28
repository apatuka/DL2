// FUN_00420aac @ 00420aac size=408 sig=undefined FUN_00420aac() cc=unknown
// callers: FUN_00421878
// callees: FUN_0041ff24,FUN_00414f04,FUN_004493dc,FUN_004a3de6,FUN_0041ff18,FUN_0046b0e4,FUN_004a2004,FUN_0042836c,FUN_0049eb44,FUN_004483d0,FUN_004202cc
// strings: \"As long as you don't have enough housing to fit all your colonists, you can't use the Colony Assistant. Build more housing or move your extra colonists to another settlement.\"|\"Oolan's Advice\"

undefined4 FUN_00420aac(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0046b0e4(param_1);
  if (iVar1 < *(short *)(param_1 + 0x30)) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_As_long_as_you_don_t_have_enough_005097a8,4,0,
                 0xb);
  }
  else {
    DAT_004b7a14 = FUN_004a3de6(0,0x33313944);
    if (DAT_004b7a14 != 0) {
      DAT_004d59a4 = 1;
      FUN_004493dc(1);
      DAT_0053b8b0 = DAT_004d59b4;
      DAT_004d59b4 = 7;
      FUN_00414f04(DAT_004b7a14);
      FUN_004a2004(DAT_004b7a14);
      FUN_0049eb44(DAT_004b7a14,1,1,7,0,FUN_00420954);
      FUN_0049eb44(DAT_004b7a14,10,1,7,0,FUN_004209c0);
      FUN_0049eb44(DAT_004b7a14,0x4a,1,7,0,FUN_00414bd8);
      FUN_0049eb44(DAT_004b7a14,0x3d,1,0x42,0,DAT_004d5b1c + 0x406);
      FUN_0049eb44(DAT_004b7a14,0x3e,1,0xb,DAT_004c48a4 != 0,0);
      FUN_0049eb44(DAT_004b7a14,0x4b,1,7,0,FUN_00414b10);
      FUN_004483d0(param_1);
      DAT_0053b8b8 = param_1;
      DAT_0053b8c0 = DAT_004c5450;
      DAT_004c5450 = 0;
      FUN_004202cc();
      iVar1 = 1000;
      do {
        FUN_0049eb44(DAT_004b7a14,iVar1,1,7,0,FUN_0041f7f0);
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x3f2);
      FUN_0041ff24();
      FUN_0041ff18();
      DAT_004d59a4 = 0;
      return 1;
    }
  }
  return 0;
}

