// FUN_0040597c @ 0040597c size=64 sig=undefined FUN_0040597c() cc=unknown
// callers: FUN_00405aac
// callees: 

int FUN_0040597c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  for (iVar1 = (&DAT_00522294)[param_1 * 0x11]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
    iVar3 = iVar2;
    if (((*(int *)(iVar1 + 0xc) == 0) && (iVar3 = iVar1, iVar2 != 0)) &&
       (iVar3 = iVar2, *(int *)(iVar2 + 8) < *(int *)(iVar1 + 8))) {
      iVar3 = iVar1;
    }
    iVar2 = iVar3;
  }
  return iVar2;
}

