// FUN_0046a9d8 @ 0046a9d8 size=54 sig=undefined FUN_0046a9d8() cc=unknown
// callers: FUN_0046ae1c
// callees: 

int FUN_0046a9d8(int param_1)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = param_1 < 0;
  if (bVar2) {
    param_1 = -param_1;
  }
  iVar1 = 0;
  if (0 < param_1) {
    do {
      if (param_1 < iVar1 * iVar1) {
        iVar1 = iVar1 + -1;
        break;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_1);
  }
  if (bVar2) {
    iVar1 = -iVar1;
  }
  return iVar1;
}

