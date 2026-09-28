// FUN_0048b165 @ 0048b165 size=91 sig=undefined FUN_0048b165() cc=unknown
// callers: 
// callees: FUN_0048f7f1

undefined4 FUN_0048b165(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_0051b8dc;
  if (param_1 != 0) {
    for (; 0 < iVar1; iVar1 = iVar1 + -1) {
      if (param_1 == *(int *)(&DAT_0065e600 + iVar1 * 4)) {
        FUN_0048f7f1(&DAT_0065e604 + iVar1 * 4,&DAT_0065e600 + iVar1 * 4,(DAT_0051b8dc - iVar1) * 4)
        ;
        DAT_0051b8dc = DAT_0051b8dc + -1;
        return 1;
      }
    }
  }
  return 0;
}

