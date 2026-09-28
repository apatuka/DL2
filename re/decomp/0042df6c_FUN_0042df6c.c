// FUN_0042df6c @ 0042df6c size=230 sig=undefined FUN_0042df6c() cc=unknown
// callers: FUN_0042e2f8,FUN_0042e2b8
// callees: FUN_0042deec,RaceInit_dc94,FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_0042df6c(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c3668 = FUN_004a3de6(0,0x31313044);
  if (DAT_004c3668 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557cbc = DAT_004d59b4;
    DAT_004d59b4 = 0x48;
    FUN_00414f04(DAT_004c3668);
    local_10 = DAT_004c367c;
    local_c = DAT_004c3678;
    local_8 = DAT_004c3684;
    local_4 = DAT_004c3680;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004c3668);
    FUN_0049eb44(DAT_004c3668,1,1,7,0,FUN_0042de68);
    FUN_0049eb44(DAT_004c3668,0x10,1,10,0,0);
    if (DAT_0058f1fc != 0) {
      FUN_0049eb44(DAT_004c3668,0xe,1,10,1,0);
    }
    RaceInit_dc94();
    FUN_0042deec();
    uVar1 = 1;
  }
  return uVar1;
}

