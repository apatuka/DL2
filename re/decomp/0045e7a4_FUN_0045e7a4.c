// FUN_0045e7a4 @ 0045e7a4 size=283 sig=undefined FUN_0045e7a4() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_00424994,FUN_0045e274,FUN_0043a1f8,ChCht,FUN_00423d84,FUN_00421a28,FUN_00468030,FUN_00423fb0

void FUN_0045e7a4(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00423fb0();
  iVar2 = DAT_004d5ad0;
  if (iVar1 == 3) {
    if (DAT_004d5a94 != 0) {
      FUN_0043a1f8(1);
      return;
    }
    if (DAT_0058f1fc == 0) {
      FUN_0043a1f8(0);
      return;
    }
    FUN_0043a1f8(2);
    return;
  }
  if (iVar1 == 4) {
    ChCht(0,1,0);
    return;
  }
  if (iVar1 == 5) {
    iVar2 = FUN_00423d84();
    if ((iVar2 != 2) && ((iVar2 != 1 || (iVar2 = ChCht(0,1,0), iVar2 != 0)))) {
      if (DAT_004d5a94 < 1) {
        DAT_0058f1ec = 1;
        return;
      }
      iVar2 = FUN_00421a28();
      if (iVar2 == 3) {
        FUN_00468030();
        return;
      }
      if (iVar2 == 4) {
        DAT_0058f1ec = 1;
        return;
      }
      if (iVar2 == 5) {
        FUN_0043a1f8(1);
        return;
      }
    }
  }
  else {
    if (iVar1 != 6) {
      return;
    }
    FUN_00424994();
    if (iVar2 != DAT_004d5ad0) {
      FUN_0045e274((int)*(char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7],
                   (int)((char *)(&DAT_005a4450)[DAT_004c5b50 * 0x2b7])[1]);
    }
  }
  return;
}

