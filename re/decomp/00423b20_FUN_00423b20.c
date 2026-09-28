// FUN_00423b20 @ 00423b20 size=62 sig=undefined FUN_00423b20() cc=unknown
// callers: RunAITurns
// callees: FUN_004229bc,FUN_00487a00

void FUN_00423b20(void)

{
  int iVar1;
  
  iVar1 = FUN_004229bc();
  if (iVar1 != 0) {
    FUN_00487a00(iVar1);
    if ((0 < DAT_004d5a94) && (iVar1 - 0x7dU < 0x12)) {
                    /* WARNING: Could not emulate address calculation at 0x00423b4f */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(&DAT_00423b6e +
                  CONCAT31((int3)(iVar1 - 0x7dU >> 8),*(undefined1 *)(iVar1 + 0x423adf)) * 4))();
      return;
    }
  }
  return;
}

