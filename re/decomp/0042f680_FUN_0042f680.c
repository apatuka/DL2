// FUN_0042f680 @ 0042f680 size=260 sig=undefined FUN_0042f680() cc=unknown
// callers: CheckBuilding
// callees: FUN_004493dc,FUN_0049eb44,FUN_0042f174,FUN_00414ea4,FUN_0042f554,FUN_004a3de6,FUN_004a2004,FUN_00414f04,FUN_0042f4d4,FUN_0045dfb0,FUN_0042f560
// strings: \"Select Ship Launch Site\"|\"Please select where to launch your ships.\"

bool FUN_0042f680(void)

{
  bool bVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c4220 = FUN_004a3de6(0,0x37303944);
  bVar1 = DAT_004c4220 != 0;
  if (bVar1) {
    DAT_004d59a4 = 1;
    FUN_004493dc(1);
    DAT_00558c78 = DAT_004d59b4;
    DAT_004d59b4 = 6;
    FUN_00414f04(DAT_004c4220);
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    FUN_00414ea4(&local_10);
    FUN_0049eb44(DAT_004c4220,2,1,7,0,FUN_0042f224);
    FUN_004a2004(DAT_004c4220);
    DAT_004c4224 = DAT_0053b870;
    FUN_0045dfb0(6);
    FUN_0042f174();
    FUN_0042f4d4();
    FUN_0049eb44(DAT_004c4220,3,1,0xf,0,PTR_s_Select_Ship_Launch_Site_00509b3c);
    FUN_0049eb44(DAT_004c4220,4,1,0xf,0,PTR_s_Please_select_where_to_launch_yo_00509b40);
    FUN_0042f560();
    FUN_0042f554();
    DAT_004d59a4 = 0;
  }
  return bVar1;
}

