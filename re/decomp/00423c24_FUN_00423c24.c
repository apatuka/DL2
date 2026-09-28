// FUN_00423c24 @ 00423c24 size=159 sig=undefined FUN_00423c24() cc=unknown
// callers: FUN_00423d84
// callees: FUN_004a2004,FUN_004493dc,FUN_004a3de6,FUN_00414f04,FUN_0049eb44
// strings: \"Would you like to save the current game before continuing?\"

undefined4 FUN_00423c24(void)

{
  DAT_004b7c00 = FUN_004a3de6(0,0x35303044);
  if (DAT_004b7c00 != 0) {
    FUN_004493dc(1);
    DAT_005574f4 = DAT_004d59b4;
    DAT_004d59b4 = 0x28;
    FUN_00414f04(DAT_004b7c00);
    FUN_004a2004(DAT_004b7c00);
    if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
      FUN_0049eb44(DAT_004b7c00,2,1,10,1,0);
    }
    FUN_0049eb44(DAT_004b7c00,7,1,0xf,0,PTR_s_Would_you_like_to_save_the_curre_00509ccc);
    return 1;
  }
  return 0;
}

