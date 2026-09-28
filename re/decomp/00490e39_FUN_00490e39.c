// FUN_00490e39 @ 00490e39 size=53 sig=undefined FUN_00490e39() cc=unknown
// callers: FUN_0046ff98
// callees: FUN_00490ce4,FUN_004989cf

undefined4 FUN_00490e39(void)

{
  if (DAT_0051daf8 != (short *)0x0) {
    while (0 < *DAT_0051daf8) {
      FUN_00490ce4(*(undefined4 *)(DAT_0051daf8 + 3));
    }
    FUN_004989cf(DAT_0051daf8);
  }
  DAT_0051daf8 = (short *)0x0;
  return 0;
}

