// FUN_00405aac @ 00405aac size=138 sig=undefined FUN_00405aac() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00405760,FUN_0040597c,FUN_00405920,FUN_00405948,FUN_004059bc

void FUN_00405aac(int param_1)

{
  int iVar1;
  
  FUN_00405920(param_1);
  iVar1 = FUN_0040597c(param_1);
  while (iVar1 != 0) {
    FUN_004059bc(param_1,iVar1);
    if (*(int *)(iVar1 + 0xc) == 0) {
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + -10;
    }
    else if (*(int *)(iVar1 + 8) < 0x1389) {
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    else {
      *(int *)(iVar1 + 8) = (int)(char)(&DAT_0059f1bf)[*(int *)(iVar1 + 4) * 0x5a + param_1 * 0x2d8]
      ;
    }
    if (*(int *)(iVar1 + 0x10) != 0) {
      FUN_00405760(iVar1);
    }
    iVar1 = FUN_0040597c(param_1);
  }
  FUN_00405948(param_1);
  return;
}

