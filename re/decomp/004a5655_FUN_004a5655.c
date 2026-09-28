// FUN_004a5655 @ 004a5655 size=68 sig=undefined FUN_004a5655() cc=unknown
// callers: 
// callees: GlobalLock

undefined4 FUN_004a5655(HGLOBAL param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  
  if ((param_1 != (HGLOBAL)0x0) && (param_2 != 0)) {
    psVar1 = GlobalLock(param_1);
    for (iVar2 = 0; iVar2 < *psVar1; iVar2 = iVar2 + 1) {
      if (param_2 == *(int *)(psVar1 + iVar2 * 4 + 8)) {
        (psVar1 + iVar2 * 4 + 8)[0] = 0;
        (psVar1 + iVar2 * 4 + 8)[1] = 0;
        return 1;
      }
    }
  }
  return 0;
}

