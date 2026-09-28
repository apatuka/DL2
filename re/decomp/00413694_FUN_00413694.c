// FUN_00413694 @ 00413694 size=197 sig=undefined FUN_00413694() cc=unknown
// callers: FUN_00413930
// callees: FUN_00414f04,FUN_004a3de6,FUN_004a60b1,FUN_0049eb44,FUN_004a2004,FUN_004493dc,FUN_00414ea4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_00413694(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004b7018 = FUN_004a3de6(0,0x39313944);
  bVar1 = DAT_004b7018 != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_005331ec = DAT_004d59b4;
    DAT_004d59b4 = 0x5a;
    FUN_00414f04(DAT_004b7018);
    local_10 = 0x53;
    local_c = 0x22;
    local_8 = 0x22d;
    local_4 = 0x1bd;
    FUN_004a60b1(&local_10,0);
    FUN_00414ea4(&local_10);
    FUN_0049eb44(DAT_004b7018,3,1,7,0,FUN_00413428);
    FUN_004a2004(DAT_004b7018);
    _DAT_005331f0 = 0;
    FUN_0049eb44(DAT_004b7018,5,1,0xb,1,0);
  }
  return bVar1;
}

