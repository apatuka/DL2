// FUN_0048b114 @ 0048b114 size=81 sig=undefined FUN_0048b114() cc=unknown
// callers: 
// callees: 

undefined4 FUN_0048b114(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_0051b8dc;
  if (param_1 != 0) {
    for (; 0 < iVar1; iVar1 = iVar1 + -1) {
      if (param_1 == *(int *)(&DAT_0065e600 + iVar1 * 4)) {
        return 1;
      }
    }
    if (DAT_0051b8dc < 10) {
      *(int *)(&DAT_0065e604 + DAT_0051b8dc * 4) = param_1;
      DAT_0051b8dc = DAT_0051b8dc + 1;
      return 1;
    }
  }
  return 0;
}

