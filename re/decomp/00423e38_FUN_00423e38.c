// FUN_00423e38 @ 00423e38 size=221 sig=undefined FUN_00423e38() cc=unknown
// callers: FUN_00423fb0
// callees: FUN_004a2004,FUN_004493dc,FUN_004a3de6,FUN_00414f04,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_00423e38(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7c28 = FUN_004a3de6(0,0x35323044);
  if (DAT_004b7c28 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005574f8 = DAT_004d59b4;
    DAT_004d59b4 = 0x50;
    FUN_00414f04(DAT_004b7c28);
    local_10 = DAT_004b7c30;
    local_c = DAT_004b7c2c;
    local_8 = DAT_004b7c38;
    local_4 = DAT_004b7c34;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7c28);
    if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
      FUN_0049eb44(DAT_004b7c28,4,1,10,1,0);
    }
    if (DAT_0058f1fc != 0) {
      FUN_0049eb44(DAT_004b7c28,3,1,10,1,0);
    }
    uVar1 = 1;
  }
  return uVar1;
}

