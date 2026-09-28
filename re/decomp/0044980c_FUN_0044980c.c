// FUN_0044980c @ 0044980c size=89 sig=undefined FUN_0044980c() cc=unknown
// callers: FUN_0043b50c,FUN_0043b2c4
// callees: FUN_0046c3fc

void FUN_0044980c(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  iVar2 = 0;
  iVar3 = 0;
  for (iVar1 = 0; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
    if ((char)(&DAT_005a43f0)[iVar1 * 0xadc] == param_1) {
      FUN_0046c3fc(&DAT_005a43d0 + iVar1 * 0xadc,&local_8,&local_c);
      iVar2 = iVar2 + local_8;
      iVar3 = iVar3 + local_c;
    }
  }
  *param_2 = iVar2;
  *param_3 = iVar3;
  return;
}

