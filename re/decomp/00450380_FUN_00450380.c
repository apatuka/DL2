// FUN_00450380 @ 00450380 size=114 sig=undefined FUN_00450380() cc=unknown
// callers: FUN_00486e34
// callees: FUN_00450340,FUN_0044fe1c,FUN_004500d8,FUN_00450204

undefined4 FUN_00450380(void)

{
  int iVar1;
  
  if (DAT_004d5a94 == 0x1b) {
    iVar1 = FUN_004500d8();
    if (iVar1 != 0) {
      return 1;
    }
  }
  iVar1 = FUN_00450204(0xd);
  if (iVar1 != 0) {
    iVar1 = FUN_0044fe1c(0xd);
    if (iVar1 != 0) {
      return 1;
    }
  }
  if ((DAT_004d5a94 != 7) && (DAT_004d5a94 != 7)) {
    iVar1 = FUN_00450204(2);
    if (iVar1 != 0) {
      iVar1 = FUN_0044fe1c(2);
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  iVar1 = FUN_00450340();
  if (iVar1 != 0) {
    return 1;
  }
  return 0;
}

