// FUN_0043ca24 @ 0043ca24 size=272 sig=undefined FUN_0043ca24() cc=unknown
// callers: FUN_00423960,FUN_0045e4f4,FUN_004226a0
// callees: FUN_004a3de6,FUN_004a2004,FUN_0043c9bc,FUN_0043c988,FUN_004839e4,FUN_0043c540,FUN_00414f04,FUN_004a60b1,FUN_0049eb44,FUN_004493dc

undefined4 FUN_0043ca24(void)

{
  int iVar1;
  int *piVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  FUN_004839e4(*(undefined4 *)(PTR_DAT_004d5988 + 0x3a),&DAT_00559da8);
  DAT_004c4900 = FUN_004a3de6(0,0x34313944);
  if ((DAT_004c4900 != 0) && (DAT_004c4904 = FUN_004a3de6(0,0x32303044), DAT_004c4904 != 0)) {
    FUN_004493dc(1);
    DAT_00559db8 = DAT_004d59b4;
    DAT_004d59b4 = 3;
    FUN_00414f04(DAT_004c4900);
    FUN_00414f04(DAT_004c4904);
    iVar1 = 1;
    piVar2 = &DAT_004fbbf6;
    do {
      FUN_0049eb44(DAT_004c4904,*piVar2 + -1,1,0x42,0,iVar1 + 7999);
      iVar1 = iVar1 + 1;
      piVar2 = (int *)((int)piVar2 + 0x32);
    } while (iVar1 < 0x30);
    local_18 = 0;
    local_14 = 0;
    local_10 = 0x280;
    local_c = 0x1e0;
    FUN_004a60b1(&local_18,0);
    FUN_004a2004(DAT_004c4900);
    FUN_004a2004(DAT_004c4904);
    FUN_0043c540();
    DAT_00559dac = 0;
    FUN_0043c9bc();
    FUN_0043c988();
    return 1;
  }
  return 0;
}

