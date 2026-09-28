// FUN_00421904 @ 00421904 size=139 sig=undefined FUN_00421904() cc=unknown
// callers: FUN_00421a28
// callees: FUN_004a2004,FUN_004493dc,FUN_004a3de6,FUN_00414f04,FUN_004a60b1

bool FUN_00421904(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7b04 = FUN_004a3de6(0,0x37323044);
  bVar1 = DAT_004b7b04 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_0053b8c8 = DAT_004d59b4;
    DAT_004d59b4 = 0x1e;
    FUN_00414f04(DAT_004b7b04);
    local_10 = DAT_004b7b0c;
    local_c = DAT_004b7b08;
    local_8 = DAT_004b7b14;
    local_4 = DAT_004b7b10;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b7b04);
  }
  return bVar1;
}

