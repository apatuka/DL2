// FUN_0042eaec @ 0042eaec size=144 sig=undefined FUN_0042eaec() cc=unknown
// callers: FUN_0042ec70
// callees: FUN_004a60b1,FUN_004493dc,FUN_0042e8c0,FUN_004a3de6,FUN_004a2004,FUN_00414f04

bool FUN_0042eaec(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c3744 = FUN_004a3de6(0,0x32333044);
  bVar1 = DAT_004c3744 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00557cc8 = DAT_004d59b4;
    DAT_004d59b4 = 0x53;
    FUN_00414f04(DAT_004c3744);
    local_10 = DAT_004c374c;
    local_c = DAT_004c3748;
    local_8 = DAT_004c3754;
    local_4 = DAT_004c3750;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004c3744);
    FUN_0042e8c0();
  }
  return bVar1;
}

