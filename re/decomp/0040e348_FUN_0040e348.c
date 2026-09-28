// FUN_0040e348 @ 0040e348 size=58 sig=undefined FUN_0040e348() cc=unknown
// callers: FUN_0040e384
// callees: FUN_00446bf0

undefined4 FUN_0040e348(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_2 + 0x7a);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((param_1 != *(char *)(iVar1 + 8)) && (iVar2 = FUN_00446bf0(iVar1), iVar2 != 0)) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

