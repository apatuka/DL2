// FUN_0042b428 @ 0042b428 size=36 sig=undefined FUN_0042b428() cc=unknown
// callers: FUN_0042b520
// callees: 

undefined4 FUN_0042b428(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 0x29U < 0x10) {
                    /* WARNING: Could not emulate address calculation at 0x0042b436 */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(&DAT_0042b453 +
                        CONCAT31((int3)(param_1 - 0x29U >> 8),*(undefined1 *)(param_1 + 0x42b41a)) *
                        4))();
    return uVar1;
  }
  return 5;
}

