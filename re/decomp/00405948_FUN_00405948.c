// FUN_00405948 @ 00405948 size=50 sig=undefined FUN_00405948() cc=unknown
// callers: FUN_00405aac
// callees: FUN_00405760

void FUN_00405948(int param_1)

{
  int *piVar1;
  
  for (piVar1 = (int *)(&DAT_00522294)[param_1 * 0x11]; piVar1 != (int *)0x0;
      piVar1 = (int *)piVar1[5]) {
    if (*piVar1 == 8) {
      FUN_00405760(piVar1);
    }
  }
  return;
}

