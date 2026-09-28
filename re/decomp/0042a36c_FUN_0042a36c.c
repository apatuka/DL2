// FUN_0042a36c @ 0042a36c size=378 sig=undefined FUN_0042a36c() cc=unknown
// callers: FUN_0042b280
// callees: FUN_00428b74,FUN_004767f0,FUN_004297e0,FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_0042a36c(void)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b9bf0 = FUN_004a3de6(0,0x38313044);
  if (DAT_004b9bf0 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557bb0 = DAT_004d59b4;
    DAT_004d59b4 = 0x4d;
    FUN_004767f0(DAT_0058f1f4,2);
    FUN_00414f04(DAT_004b9bf0);
    local_14 = DAT_004b9bf8;
    local_10 = DAT_004b9bf4;
    local_c = DAT_004b9c00;
    local_8 = DAT_004b9bfc;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004b9bf0);
    FUN_0049eb44(DAT_004b9bf0,1,1,7,0,FUN_0042a25c);
    switch(DAT_004d5aec) {
    case 2:
      FUN_0049eb44(DAT_004b9bf0,0xd,1,10,1,0);
    case 3:
      FUN_0049eb44(DAT_004b9bf0,0xe,1,10,1,0);
    case 4:
      FUN_0049eb44(DAT_004b9bf0,0xf,1,10,1,0);
    case 5:
      FUN_0049eb44(DAT_004b9bf0,0x10,1,10,1,0);
    case 6:
      FUN_0049eb44(DAT_004b9bf0,0x11,1,10,1,0);
    default:
      FUN_004297e0();
      piVar3 = &DAT_00557bb4;
    }
    for (iVar1 = 0; iVar1 < DAT_004d5aec + -1; iVar1 = iVar1 + 1) {
      if ((&DAT_0059f161)[*piVar3 * 0x2d8] != '\0') {
        FUN_00428b74(iVar1);
        break;
      }
      piVar3 = piVar3 + 1;
    }
    uVar2 = 1;
  }
  return uVar2;
}

