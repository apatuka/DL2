// FUN_00416810 @ 00416810 size=416 sig=undefined FUN_00416810() cc=unknown
// callers: FUN_00416af0
// callees: FUN_004493dc,FUN_0046784c,FUN_0049eb44,FUN_004a2004,FUN_004a60b1,FUN_004a3de6,FUN_00414f04,FUN_0049117e

undefined4 FUN_00416810(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  DAT_004b769c = FUN_004a3de6(0,0x35333044);
  if (DAT_004b769c == 0) {
    uVar2 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005332a8 = DAT_004d59b4;
    DAT_004d59b4 = 0x15;
    FUN_00414f04(DAT_004b769c);
    local_18 = DAT_004b76a4;
    local_14 = DAT_004b76a0;
    local_10 = DAT_004b76ac;
    local_c = DAT_004b76a8;
    FUN_004a60b1(&local_18,0);
    FUN_004a2004(DAT_004b769c);
    FUN_0049eb44(DAT_004b769c,4,1,0xb,1,0);
    DAT_005332ac = 0;
    if (DAT_004d5aa0 == '\0') {
      uVar2 = 1;
      iVar1 = FUN_0046784c(0);
      FUN_0049eb44(DAT_004b769c,0xd,1,10,iVar1 == 0,uVar2);
    }
    else {
      FUN_0049eb44(DAT_004b769c,0xd,1,10,1,1);
    }
    if (DAT_004d5aa0 != '\0') {
      uVar2 = FUN_0049117e(0,0x54494445,0);
      FUN_0049eb44(DAT_004b769c,2,1,0xf,0,uVar2);
      if (DAT_00559d9c == 0) {
        uVar2 = FUN_0049117e(0,0x54494445,2);
        FUN_0049eb44(DAT_004b769c,3,1,0xf,0,uVar2);
      }
      else if (DAT_00559d9c == 1) {
        uVar2 = FUN_0049117e(0,0x54494445,1);
        FUN_0049eb44(DAT_004b769c,3,1,0xf,0,uVar2);
      }
      else if (DAT_00559d9c == 2) {
        uVar2 = FUN_0049117e(0,0x54494445,3);
        FUN_0049eb44(DAT_004b769c,3,1,0xf,0,uVar2);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

