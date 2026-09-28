// FUN_0046f908 @ 0046f908 size=46 sig=undefined FUN_0046f908() cc=unknown
// callers: FUN_0044f110,FUN_0046f938
// callees: qsort

void FUN_0046f908(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_0058f21c;
  do {
    *piVar2 = iVar1;
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x4b0);
  qsort(&DAT_0058f21c,0x4b0,4,FUN_0046f8cc);
  return;
}

