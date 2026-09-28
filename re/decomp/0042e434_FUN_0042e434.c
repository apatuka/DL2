// FUN_0042e434 @ 0042e434 size=139 sig=undefined FUN_0042e434() cc=unknown
// callers: FUN_0042e2f8,FUN_004618e8,FUN_00468ea4,RaceInit
// callees: FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_004a60b1

bool FUN_0042e434(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c36ac = FUN_004a3de6(0,0x30313044);
  bVar1 = DAT_004c36ac != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00557cc0 = DAT_004d59b4;
    DAT_004d59b4 = 0x47;
    FUN_00414f04(DAT_004c36ac);
    local_10 = DAT_004c36b4;
    local_c = DAT_004c36b0;
    local_8 = DAT_004c36bc;
    local_4 = DAT_004c36b8;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004c36ac);
  }
  return bVar1;
}

