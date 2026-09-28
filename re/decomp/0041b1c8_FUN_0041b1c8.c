// FUN_0041b1c8 @ 0041b1c8 size=182 sig=undefined FUN_0041b1c8() cc=unknown
// callers: FUN_0041b280
// callees: FUN_004493dc,FUN_0041acf8,FUN_0049eb44,FUN_004a2004,FUN_0041acbc,FUN_004a60b1,FUN_004a3de6,FUN_00414f04

bool FUN_0041b1c8(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b76f8 = FUN_004a3de6(0,0x32303944);
  bVar1 = DAT_004b76f8 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_0053b338 = DAT_004d59b4;
    DAT_004d59b4 = 0xd;
    DAT_0053b268 = 1;
    FUN_00414f04(DAT_004b76f8);
    DAT_004b76f0 = 0;
    FUN_0041acbc();
    FUN_0041acf8();
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    FUN_004a60b1(&local_10,0);
    FUN_004a2004(DAT_004b76f8);
    FUN_0049eb44(DAT_004b76f8,6,1,7,0,FUN_0041ab54);
  }
  return bVar1;
}

