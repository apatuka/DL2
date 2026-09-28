// FUN_00427ca0 @ 00427ca0 size=211 sig=undefined FUN_00427ca0() cc=unknown
// callers: FUN_00427e30
// callees: FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1
// strings: \"Game 1\"

bool FUN_00427ca0(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7d80 = FUN_004a3de6(0,0x31323044);
  bVar1 = DAT_004b7d80 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00557b98 = DAT_004d59b4;
    DAT_004d59b4 = 0x3b;
    FUN_00414f04(DAT_004b7d80);
    local_10 = DAT_004b7d88;
    local_c = DAT_004b7d84;
    local_8 = DAT_004b7d90;
    local_4 = DAT_004b7d8c;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7d80);
    FUN_0049eb44(DAT_004b7d80,4,1,0xf,0,s_Game_1_005097c4);
    FUN_0049eb44(DAT_004b7d80,4,1,0x1c,4,0);
    FUN_0049eb44(DAT_004b7d80,4,1,0x34,1,0);
  }
  return bVar1;
}

