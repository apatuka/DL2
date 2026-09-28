// FUN_00471c1c @ 00471c1c size=93 sig=undefined FUN_00471c1c() cc=unknown
// callers: FUN_00404048,FUN_00471cec,FUN_00471c7c
// callees: memset

void FUN_00471c1c(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  memset(param_2,0,0x2c);
  for (iVar4 = 1; iVar4 <= DAT_004d5b18; iVar4 = iVar4 + 1) {
    if ((char)(&DAT_005a43f0)[iVar4 * 0xadc] == param_1) {
      iVar2 = 0;
      piVar1 = (int *)(&DAT_005a440a + iVar4 * 0xadc);
      piVar3 = param_2;
      do {
        *piVar3 = *piVar3 + *piVar1;
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
        piVar1 = piVar1 + 1;
      } while (iVar2 < 0xb);
    }
  }
  return;
}

