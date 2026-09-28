// FUN_0042b498 @ 0042b498 size=57 sig=undefined FUN_0042b498() cc=unknown
// callers: FUN_0042b520
// callees: FUN_0049eb44

void FUN_0042b498(int param_1)

{
  if (param_1 - 0x29U < 0x10) {
                    /* WARNING: Could not emulate address calculation at 0x0042b4a6 */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(&DAT_0042b4c3 + CONCAT31((int3)(param_1 - 0x29U >> 8),(&DAT_0042b48a)[param_1]) * 4
                ))();
    return;
  }
  FUN_0049eb44(DAT_004bda5c,0x39,1,0xc,0,0);
  return;
}

