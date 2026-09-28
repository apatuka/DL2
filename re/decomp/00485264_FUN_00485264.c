// FUN_00485264 @ 00485264 size=99 sig=undefined FUN_00485264() cc=unknown
// callers: FUN_00485668
// callees: FUN_00446bf0

undefined4 FUN_00485264(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_2 + 0x7a);
  while( true ) {
    if (iVar1 == 0) {
      iVar1 = *(int *)(param_2 + 0x76);
      while( true ) {
        if (iVar1 == 0) {
          return 0;
        }
        if ((param_1 != *(char *)(iVar1 + 8)) && (iVar2 = FUN_00446bf0(iVar1), iVar2 == 0)) break;
        iVar1 = *(int *)(iVar1 + 0x54);
      }
      return 1;
    }
    if ((param_1 != *(char *)(iVar1 + 8)) && (iVar2 = FUN_00446bf0(iVar1), iVar2 == 0)) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

