// FUN_0046257c @ 0046257c size=166 sig=undefined FUN_0046257c() cc=unknown
// callers: FUN_00463014
// callees: 

void FUN_0046257c(int param_1)

{
  int *piVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  short *local_10;
  int local_8;
  
  local_8 = 0;
  local_10 = &DAT_005a0552;
  for (iVar4 = 0; iVar4 < DAT_004d5b1b; iVar4 = iVar4 + 1) {
    piVar1 = &DAT_005a4450 + param_1 * 0x2b7 + local_8;
    psVar2 = local_10;
    for (iVar3 = 0; iVar3 < DAT_004d5b1a; iVar3 = iVar3 + 1) {
      if (*psVar2 == param_1) {
        *piVar1 = (int)(&DAT_005a0550 + iVar4 * 400 + iVar3 * 10);
        *(char *)*piVar1 = (char)iVar3;
        *(char *)(*piVar1 + 1) = (char)iVar4;
        local_8 = local_8 + 1;
        piVar1 = piVar1 + 1;
      }
      psVar2 = psVar2 + 5;
    }
    local_10 = local_10 + 200;
  }
  (&DAT_005a444e)[param_1 * 0xadc] = (undefined1)local_8;
  return;
}

