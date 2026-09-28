// FUN_0041f384 @ 0041f384 size=296 sig=undefined FUN_0041f384() cc=unknown
// callers: FUN_0041f740
// callees: FUN_0041ed78,FUN_0041f0b8,FUN_00414f04,FUN_0041e914,FUN_004493dc,FUN_004a3de6,FUN_004a60b1,FUN_0041ed44,FUN_004a2004,FUN_0049eb44,FUN_0041f198

undefined4 FUN_0041f384(int param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b7974 = FUN_004a3de6(0,0x33333044);
  if (DAT_004b7974 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_0053b884 = DAT_004d59b4;
    DAT_004d59b4 = 0x11;
    FUN_00414f04(DAT_004b7974);
    local_14 = DAT_004b797c;
    local_10 = DAT_004b7978;
    local_c = DAT_004b7984;
    local_8 = DAT_004b7980;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004b7974);
    FUN_0049eb44(DAT_004b7974,1,1,7,0,FUN_0041f2c8);
    FUN_0041f0b8();
    FUN_0049eb44(DAT_004b7974,0xc,1,0xb,1,0);
    if (param_1 == 0) {
      FUN_0041f198(0x1f);
      DAT_0053b8a8 = 0x1f;
      FUN_0041ed78();
    }
    else {
      FUN_0041f198(0x24);
      DAT_0053b8a8 = 0x24;
      FUN_0041ed44();
      FUN_0049eb44(DAT_004b7974,0x1d,1,0x34,1,0);
    }
    FUN_0041e914();
    FUN_0049eb44(DAT_004b7974,9,1,0xf,0,0);
    uVar1 = 1;
  }
  return uVar1;
}

