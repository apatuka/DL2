// FUN_00462624 @ 00462624 size=201 sig=undefined FUN_00462624() cc=unknown
// callers: FUN_00466218,FUN_00466128
// callees: FUN_0046237c

void FUN_00462624(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  short *psVar5;
  short *local_14;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_14 = &DAT_005a0552;
  for (local_8 = 0; local_8 < DAT_004d5b1b; local_8 = local_8 + 1) {
    piVar3 = &DAT_005a4450 + param_1 * 0x2b7 + local_c;
    psVar5 = local_14;
    for (iVar4 = 0; iVar4 < DAT_004d5b1a; iVar4 = iVar4 + 1) {
      if (*psVar5 == param_1) {
        iVar2 = local_8 * 400 + iVar4 * 10;
        *piVar3 = (int)(&DAT_005a0550 + iVar2);
        (&DAT_005a0550)[iVar2] = (char)iVar4;
        (&DAT_005a0551)[iVar2] = (undefined1)local_8;
        uVar1 = FUN_0046237c(iVar4,local_8,param_1);
        *(undefined1 *)(*piVar3 + 4) = uVar1;
        local_c = local_c + 1;
        piVar3 = piVar3 + 1;
      }
      psVar5 = psVar5 + 5;
    }
    local_14 = local_14 + 200;
  }
  (&DAT_005a444e)[param_1 * 0xadc] = (undefined1)local_c;
  return;
}

