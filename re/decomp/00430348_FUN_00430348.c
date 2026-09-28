// FUN_00430348 @ 00430348 size=197 sig=undefined FUN_00430348() cc=unknown
// callers: FUN_00430abc
// callees: FUN_004a60b1,FUN_004493dc,FUN_0049eb44,FUN_004a3de6,FUN_004a2004,FUN_00414f04,FUN_0042fb64

bool FUN_00430348(void)

{
  bool bVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004c4294 = FUN_004a3de6(0,0x34313044);
  bVar1 = DAT_004c4294 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00558cbc = DAT_004d59b4;
    DAT_004d59b4 = 0x18;
    FUN_00414f04(DAT_004c4294);
    FUN_0049eb44(DAT_004c4294,0x25,1,7,0,&LAB_00414a6c);
    FUN_0049eb44(DAT_004c4294,0x27,1,7,0,&LAB_00414a6c);
    local_14 = DAT_004c429c;
    local_10 = DAT_004c4298;
    local_c = DAT_004c42a4;
    local_8 = DAT_004c42a0;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004c4294);
    FUN_0042fb64();
  }
  return bVar1;
}

