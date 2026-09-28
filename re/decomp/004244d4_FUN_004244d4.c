// FUN_004244d4 @ 004244d4 size=144 sig=undefined FUN_004244d4() cc=unknown
// callers: FUN_00424994
// callees: FUN_004a2004,FUN_004493dc,FUN_00423fdc,FUN_004a3de6,FUN_00414f04,FUN_004a60b1

bool FUN_004244d4(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7c3c = FUN_004a3de6(0,0x34323044);
  bVar1 = DAT_004b7c3c != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_005574fc = DAT_004d59b4;
    DAT_004d59b4 = 0x16;
    FUN_00414f04(DAT_004b7c3c);
    local_10 = DAT_004b7c44;
    local_c = DAT_004b7c40;
    local_8 = DAT_004b7c4c;
    local_4 = DAT_004b7c48;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7c3c);
    FUN_00423fdc();
  }
  return bVar1;
}

