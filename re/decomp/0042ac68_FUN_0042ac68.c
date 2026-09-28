// FUN_0042ac68 @ 0042ac68 size=135 sig=undefined FUN_0042ac68() cc=unknown
// callers: FUN_0042b280
// callees: FUN_0048db5d,FUN_0042a2c4,FUN_004a2cb5

longlong FUN_0042ac68(void)

{
  int iVar1;
  longlong lVar2;
  uint local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar1 = FUN_004a2cb5(DAT_004b9bf0,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b9bf0 + 100) == 0)) {
    if (local_8 - 8 < 0x3e) {
                    /* WARNING: Could not emulate address calculation at 0x0042acd0 */
                    /* WARNING: Treating indirect jump as call */
      lVar2 = (**(code **)(&DAT_0042ad1b +
                          CONCAT31((int3)(local_8 - 8 >> 8),*(undefined1 *)(local_8 + 0x42acd5)) * 4
                          ))();
      return lVar2;
    }
  }
  FUN_0042a2c4();
  DAT_004d59a4 = 0;
  return (ulonglong)local_8 << 0x20;
}

