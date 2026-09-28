// FUN_0042bc50 @ 0042bc50 size=127 sig=undefined FUN_0042bc50() cc=unknown
// callers: FUN_0042c054
// callees: FUN_0048db5d,FUN_004a2cb5,FUN_0042ba98
// strings: \"\\r\\r\\r\\r\\r\\r\\r\"

undefined4 FUN_0042bc50(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c [6];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042ba98();
  iVar1 = FUN_004a2cb5(DAT_004bda5c,local_1c);
  if (((iVar1 == 0) && (local_1c[0] != 0)) && (*(int *)(DAT_004bda5c + 100) == 0)) {
    if (local_1c[0] - 0x1fU < 0x1f) {
                    /* WARNING: Could not emulate address calculation at 0x0042bcb3 */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(&DAT_0042bcdf +
                          CONCAT31((int3)(local_1c[0] - 0x1fU >> 8),
                                   *(undefined1 *)(local_1c[0] + 0x42bca1)) * 4))();
      return uVar2;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

