// FUN_0042278c @ 0042278c size=39 sig=undefined FUN_0042278c() cc=unknown
// callers: FUN_004234d4,FUN_00423380,FUN_004228d4,FUN_004229bc,FUN_00423690,FUN_004233e0
// callees: 

int FUN_0042278c(int param_1)

{
  int iVar1;
  short *psVar2;
  
  iVar1 = 0;
  psVar2 = &DAT_004fc912;
  do {
    if (param_1 == *psVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    psVar2 = psVar2 + 9;
  } while (iVar1 < 0x9d);
  return 0;
}

