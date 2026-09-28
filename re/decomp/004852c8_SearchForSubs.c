// SearchForSubs @ 004852c8 size=123 sig=undefined SearchForSubs() cc=unknown
// callers: FUN_00485668
// callees: FUN_0046c9d8
// strings: \"SearchForSubs\"

/* auto-named from string evidence: SearchForSubs */

void SearchForSubs(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  for (iVar1 = *(int *)(param_2 + 0x7a); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
    if (((param_1 != *(char *)(iVar1 + 8)) && (*(char *)(iVar1 + 0x25) == '\x0f')) &&
       (uVar2 = FUN_0046c9d8(100,s_SearchForSubs_005123ec), uVar2 < 0x32)) {
      *(undefined1 *)(iVar1 + 0x25) = 0;
    }
  }
  for (iVar1 = *(int *)(param_2 + 0x76); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
    if (((param_1 != *(char *)(iVar1 + 8)) && (*(char *)(iVar1 + 0x25) == '\x0f')) &&
       (uVar2 = FUN_0046c9d8(100,s_SearchForSubs_005123ec), uVar2 < 0x32)) {
      *(undefined1 *)(iVar1 + 0x25) = 0;
    }
  }
  return;
}

