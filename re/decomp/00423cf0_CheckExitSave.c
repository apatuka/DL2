// CheckExitSave @ 00423cf0 size=146 sig=undefined CheckExitSave() cc=unknown
// callers: FUN_00423d84
// callees: FUN_00426594,DebugMessage,FUN_00423bf0,FUN_004a2cb5,FUN_00423cc4,FUN_0048db5d
// strings: \"NULL gpExitSave in CheckExitSave()\"

/* auto-named from string evidence: CheckExitSave */

longlong CheckExitSave(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004b7c00 == 0) {
    DebugMessage(s_NULL_gpExitSave_in_CheckExitSave_004b7c04);
    return (ulonglong)local_4 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00423bf0();
  iVar1 = FUN_004a2cb5(DAT_004b7c00,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7c00 + 100) == 0)) {
    if (local_4 - 2 < 3) {
      FUN_00423cc4();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
    if (local_4 - 2 == 3) {
      FUN_00426594(&DAT_004d4d64);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

