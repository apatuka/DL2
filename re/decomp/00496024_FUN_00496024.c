// FUN_00496024 @ 00496024 size=40 sig=undefined FUN_00496024() cc=unknown
// callers: FUN_00482b04
// callees: FUN_0048a3ef

void FUN_00496024(void)

{
  int iVar1;
  
  if (DAT_0051e08c != (int *)0x0) {
    for (iVar1 = *DAT_0051e08c; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      FUN_0048a3ef(iVar1);
    }
  }
  return;
}

