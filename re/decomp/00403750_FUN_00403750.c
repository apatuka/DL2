// FUN_00403750 @ 00403750 size=263 sig=undefined FUN_00403750() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00403408,FUN_0046ca40

void FUN_00403750(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  char *local_14;
  int local_c;
  int local_8;
  
  iVar4 = 0;
  local_8 = -1;
  local_c = -1;
  piVar5 = &DAT_0055a804;
  local_14 = &DAT_0059f161;
  piVar3 = (int *)(&DAT_005220a4 + param_1 * 0x1c);
  do {
    if (((*local_14 != '\0') && (iVar4 != param_1)) && (*piVar3 < 8)) {
      iVar1 = ((8 - *piVar3) * 0x4b) / 0x3a +
              (((&DAT_0055a804)[param_1] - *piVar5) * 0x19) / ((&DAT_0055a804)[param_1] + *piVar5);
      if (local_c < iVar1) {
        local_c = iVar1;
        local_8 = iVar4;
      }
    }
    iVar4 = iVar4 + 1;
    piVar5 = piVar5 + 1;
    piVar3 = piVar3 + 1;
    local_14 = local_14 + 0x2d8;
  } while (iVar4 < 7);
  if ((local_8 != -1) &&
     ((1 << ((byte)local_8 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) {
    uVar2 = FUN_0046ca40();
    if ((int)(uVar2 % 100) < local_c) {
      FUN_00403408(param_1,local_8);
    }
  }
  return;
}

