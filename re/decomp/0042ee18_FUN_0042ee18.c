// FUN_0042ee18 @ 0042ee18 size=476 sig=undefined FUN_0042ee18() cc=unknown
// callers: FUN_0042f0c4
// callees: FUN_004a60b1,FUN_004493dc,FUN_004503f4,FUN_0049eb44,FUN_004a3de6,FUN_004a2004,FUN_00414f04,FUN_0041244c,DisableMainInterface,FUN_00482ac4,FUN_0042edc4
// strings: \"G000G001G002G003G004G005\"

undefined4 FUN_0042ee18(int param_1)

{
  undefined4 uVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [4];
  
  DAT_004c3818 = 0;
  DAT_004c3800 = FUN_004a3de6(0,0x34333044);
  if (DAT_004c3800 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    if ((DAT_004d59b4 == 0x32) && (DAT_004c48a0 != 0)) {
      DisableMainInterface(1);
    }
    DAT_00557ccc = DAT_004d59b4;
    DAT_004d59b4 = 0x54;
    FUN_00414f04(DAT_004c3800);
    local_18 = DAT_004c3808;
    local_14 = DAT_004c3804;
    local_10 = DAT_004c3810;
    local_c = DAT_004c380c;
    FUN_004a60b1(&local_18,0);
    FUN_0049eb44(DAT_004c3800,1,1,7,0,&LAB_0042ec90);
    if (param_1 < 8) {
      FUN_0049eb44(DAT_004c3800,1,1,0x42,0,
                   *(undefined4 *)(&DAT_004c3b34 + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 4))
      ;
    }
    else {
      FUN_0049eb44(DAT_004c3800,1,1,0x42,0,0x3f3);
    }
    FUN_004a2004(DAT_004c3800);
    if (param_1 < 8) {
      uVar1 = FUN_004503f4((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],0x1e,param_1);
      DAT_00557cd0 = FUN_0041244c(DAT_004d5a5c,uVar1,local_8);
    }
    else {
      DAT_00557cd0 = FUN_0042edc4();
    }
    if (((DAT_004d5ab0 != 0) && (DAT_004d5aa8 != 0)) && (DAT_004c3814 == '\0')) {
      DAT_004c38e0 = *(int *)(s_G000G001G002G003G004G005_004c381c +
                             param_1 * 4 + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 0x1c);
      if (DAT_004c38e0 != 0) {
        FUN_00482ac4(DAT_004c38e0,0,0,0,0,0);
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

