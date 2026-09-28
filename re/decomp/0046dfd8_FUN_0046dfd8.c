// FUN_0046dfd8 @ 0046dfd8 size=44 sig=undefined FUN_0046dfd8() cc=unknown
// callers: FUN_0046e064
// callees: 

undefined4 FUN_0046dfd8(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x7a);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (param_2 == *(char *)(iVar1 + 8)) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

