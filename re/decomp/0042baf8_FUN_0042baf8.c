// FUN_0042baf8 @ 0042baf8 size=299 sig=undefined FUN_0042baf8() cc=unknown
// callers: FUN_0042c054
// callees: FUN_0042b870,FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

bool FUN_0042baf8(void)

{
  bool bVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004bda5c = FUN_004a3de6(0,0x36313044);
  bVar1 = DAT_004bda5c != 0;
  if (bVar1) {
    FUN_004493dc(1);
    DAT_00557bf4 = DAT_004d59b4;
    DAT_004d59b4 = 0x3e;
    FUN_00414f04(DAT_004bda5c);
    local_14 = DAT_004bda64;
    local_10 = DAT_004bda60;
    local_c = DAT_004bda6c;
    local_8 = DAT_004bda68;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004bda5c);
    FUN_0049eb44(DAT_004bda5c,0x27,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x29,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x2c,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x2f,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x32,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x35,1,7,0,FUN_0042b99c);
    FUN_0049eb44(DAT_004bda5c,0x38,1,7,0,FUN_0042b99c);
    FUN_0042b870();
  }
  return bVar1;
}

