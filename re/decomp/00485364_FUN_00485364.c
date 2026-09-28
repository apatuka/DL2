// FUN_00485364 @ 00485364 size=141 sig=undefined FUN_00485364() cc=unknown
// callers: FUN_00485668
// callees: FUN_00446bf0,FUN_0046c9d8
// strings: \"Uncloak\"

void FUN_00485364(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  for (iVar1 = *(int *)(param_2 + 0x7a); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
    if ((((param_1 != *(char *)(iVar1 + 8)) && (iVar2 = FUN_00446bf0(iVar1), iVar2 != 0)) &&
        (iVar2 = FUN_0046c9d8(2,s_Uncloak_005123fa), iVar2 == 0)) &&
       (*(char *)(iVar1 + 6) != '\x1e')) {
      *(undefined1 *)(iVar1 + 0x25) = 0;
    }
  }
  for (iVar1 = *(int *)(param_2 + 0x76); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
    if (((param_1 != *(char *)(iVar1 + 8)) && (iVar2 = FUN_00446bf0(iVar1), iVar2 != 0)) &&
       ((iVar2 = FUN_0046c9d8(2,s_Uncloak_005123fa), iVar2 == 0 && (*(char *)(iVar1 + 6) != '\x1e'))
       )) {
      *(undefined1 *)(iVar1 + 0x25) = 0;
    }
  }
  return;
}

