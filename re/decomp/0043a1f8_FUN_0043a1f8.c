// FUN_0043a1f8 @ 0043a1f8 size=297 sig=undefined FUN_0043a1f8() cc=unknown
// callers: FUN_0046903c,FUN_00468d3c,FUN_0045e7a4,FUN_004680ac,FUN_004687d4,FUN_0047361c
// callees: FUN_0043a854,FUN_0043997c,FUN_004399dc,FUN_00468da0,FUN_004360ec,FUN_004780e4,FUN_00461c68,FUN_00439e6c,FUN_004618e8,FUN_00439e98,FUN_0044a000

undefined4 FUN_0043a1f8(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_004399dc(param_1);
  if (iVar1 == 0) {
    uVar2 = 0x35;
  }
  else {
    FUN_0043997c();
    do {
      iVar1 = FUN_00439e98();
    } while (iVar1 == 0);
    FUN_00439e6c();
    if ((DAT_005598e0 != 0) && (DAT_004d59b4 == 0x2a)) {
      FUN_004360ec();
    }
    if (iVar1 == 6) {
      if (DAT_004d5974 != 0) {
        FUN_0044a000();
      }
      if (DAT_004d5a88 == 0) {
        uVar2 = 0x35;
      }
      else {
        uVar2 = 0x3e;
        DAT_004d5a88 = 0;
      }
    }
    else {
      switch(DAT_005598dc) {
      case 0:
      case 1:
      case 3:
        FUN_004780e4(DAT_0058f1f4,1);
        iVar1 = DAT_004d59b4;
        iVar3 = FUN_004618e8(&DAT_005597d5,1);
        if (iVar3 == 0) {
          uVar2 = 0x35;
        }
        else {
          if ((iVar1 == 1) || (iVar1 == 0)) {
            DAT_004d59b4 = 0;
            FUN_0043a854();
            FUN_0044a000();
          }
          DAT_004d598c = 1;
          uVar2 = 0x46;
        }
        break;
      case 2:
      case 5:
        uVar2 = FUN_00468da0(&DAT_005597d5);
        break;
      case 4:
        iVar1 = FUN_00461c68(&DAT_005597d5);
        if (iVar1 == 0) {
          uVar2 = 0x3e;
          DAT_004d5a88 = 0;
        }
        else {
          uVar2 = 0x43;
        }
        break;
      default:
        uVar2 = 0x35;
      }
    }
  }
  return uVar2;
}

