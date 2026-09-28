// FUN_004288c0 @ 004288c0 size=353 sig=undefined FUN_004288c0() cc=unknown
// callers: FUN_00428b48
// callees: FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_004288c0(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7e0c = FUN_004a3de6(0,0x30323044);
  if (DAT_004b7e0c == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557bac = DAT_004d59b4;
    DAT_004d59b4 = 0x37;
    FUN_00414f04(DAT_004b7e0c);
    local_10 = DAT_004b7e14;
    local_c = DAT_004b7e10;
    local_8 = DAT_004b7e1c;
    local_4 = DAT_004b7e18;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7e0c);
    if (DAT_004d59ac == 0) {
      FUN_0049eb44(DAT_004b7e0c,7,1,0xb,1,0);
      FUN_0049eb44(DAT_004b7e0c,8,1,0xb,1,0);
      DAT_004d5a4c = 1;
      DAT_004d5a50 = 8;
      FUN_0049eb44(DAT_004b7e0c,6,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004b7e0c,6,1,0xb,1,0);
      FUN_0049eb44(DAT_004b7e0c,8,1,0xb,1,0);
      DAT_004d5a4c = 0;
      DAT_004d5a50 = 8;
      if (DAT_004d513c != 0) {
        FUN_0049eb44(DAT_004b7e0c,6,1,10,1,0);
        FUN_0049eb44(DAT_004b7e0c,7,1,10,1,0);
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

