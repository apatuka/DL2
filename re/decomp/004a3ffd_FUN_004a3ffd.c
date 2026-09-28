// FUN_004a3ffd @ 004a3ffd size=40 sig=undefined FUN_004a3ffd() cc=unknown
// callers: FUN_004169e8
// callees: FUN_0049f83e

void FUN_004a3ffd(void)

{
  int iVar1;
  
  if (DAT_0051e384 != (int *)0x0) {
    for (iVar1 = *DAT_0051e384; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      FUN_0049f83e(iVar1);
    }
  }
  return;
}

