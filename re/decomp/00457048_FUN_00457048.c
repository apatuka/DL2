// FUN_00457048 @ 00457048 size=152 sig=undefined FUN_00457048() cc=unknown
// callers: FUN_004570e0,FUN_0043e0dc,FUN_004526b0,FUN_0043e058
// callees: FUN_0045539c,FUN_00450de0,FUN_00451034

bool FUN_00457048(void)

{
  int iVar1;
  int iVar2;
  
  if (0x2ee < DAT_005649d4) {
    return true;
  }
  if (DAT_005649d4 != 0x2ee) {
    iVar1 = FUN_00451034();
    if (iVar1 != 0) {
      if (DAT_005649d8 == 0xffffffff) {
        DAT_005649d8 = DAT_005649d4 + 0x14;
      }
      return DAT_005649d8 <= DAT_005649d4;
    }
    return false;
  }
  iVar1 = FUN_00451034();
  if (iVar1 == 0) {
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
      iVar2 = FUN_00450de0(iVar1);
      if (iVar2 != 0) {
        FUN_0045539c(iVar1);
      }
    }
    DAT_005649e0 = 0;
  }
  DAT_005649d4 = DAT_005649d4 + 1;
  return true;
}

