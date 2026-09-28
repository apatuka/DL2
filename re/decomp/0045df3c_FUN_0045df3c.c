// FUN_0045df3c @ 0045df3c size=81 sig=undefined FUN_0045df3c() cc=unknown
// callers: FUN_0045d418,FUN_0045d984,FUN_0045d6a4
// callees: FUN_0045deb0

void FUN_0045df3c(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  
  for (iVar3 = 0; iVar3 < DAT_004d5b1b; iVar3 = iVar3 + 1) {
    puVar2 = &DAT_005a0550 + iVar3 * 400;
    for (iVar1 = 0; iVar1 < DAT_004d5b1a; iVar1 = iVar1 + 1) {
      if (*(short *)(puVar2 + 2) == param_1) {
        FUN_0045deb0(iVar1,iVar3);
      }
      puVar2 = puVar2 + 10;
    }
  }
  return;
}

