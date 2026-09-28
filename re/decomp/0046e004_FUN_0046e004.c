// FUN_0046e004 @ 0046e004 size=93 sig=undefined FUN_0046e004() cc=unknown
// callers: FUN_0046e064
// callees: 

undefined4 FUN_0046e004(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x76);
  while( true ) {
    if (iVar1 == 0) {
      iVar1 = *(int *)(param_1 + 0x7a);
      while( true ) {
        if (iVar1 == 0) {
          return 0;
        }
        if ((param_2 == *(char *)(iVar1 + 8)) && (*(char *)(iVar1 + 6) == '\x1c')) break;
        iVar1 = *(int *)(iVar1 + 0x54);
      }
      return 1;
    }
    if ((param_2 == *(char *)(iVar1 + 8)) && (*(char *)(iVar1 + 6) == '\x1c')) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

