// FUN_0042e6f4 @ 0042e6f4 size=202 sig=undefined FUN_0042e6f4() cc=unknown
// callers: FUN_0042e8a0
// callees: FUN_004a60b1,FUN_004493dc,FUN_0049eb44,FUN_004a3de6,FUN_004a2004,FUN_00414f04

bool FUN_0042e6f4(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c3730 = FUN_004a3de6(0,0x31333044);
  bVar1 = DAT_004c3730 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00557cc4 = DAT_004d59b4;
    DAT_004d59b4 = 0x52;
    FUN_00414f04(DAT_004c3730);
    local_10 = DAT_004c3738;
    local_c = DAT_004c3734;
    local_8 = DAT_004c3740;
    local_4 = DAT_004c373c;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004c3730);
    FUN_0049eb44(DAT_004c3730,4,1,0xf,0,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
    FUN_0049eb44(DAT_004c3730,4,1,0x34,1,0);
  }
  return bVar1;
}

