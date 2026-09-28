// FUN_00423d84 @ 00423d84 size=81 sig=undefined FUN_00423d84() cc=unknown
// callers: WaitSync,FUN_0045ea44,FUN_0045e7a4,FUN_00472da4
// callees: FUN_00423bf0,CheckExitSave,FUN_00423c24

undefined4 FUN_00423d84(void)

{
  int iVar1;
  
  iVar1 = FUN_00423c24();
  if (iVar1 == 0) {
    return 7;
  }
  FUN_00423bf0();
  iVar1 = 0;
  while (((iVar1 != 2 && (iVar1 != 3)) && (iVar1 != 4))) {
    iVar1 = CheckExitSave();
  }
  if (iVar1 == 2) {
    return 1;
  }
  if (iVar1 == 3) {
    return 7;
  }
  if (iVar1 != 4) {
    return 7;
  }
  return 2;
}

