// FUN_00401718 @ 00401718 size=278 sig=undefined FUN_00401718() cc=unknown
// callers: FUN_00402548
// callees: FUN_00401670

void FUN_00401718(int param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = FUN_00401670(param_1,(int)*(char *)(param_1 + 0x20));
  iVar3 = 0;
  piVar2 = param_2;
  do {
    *piVar2 = 0;
    if ((uVar1 & 1) != 0) {
      piVar4 = &DAT_004b5260 + iVar3;
      if (*piVar4 < param_2[iVar3]) {
        piVar4 = param_2 + iVar3;
      }
      *piVar2 = *piVar4;
    }
    if ((uVar1 & 4) != 0) {
      piVar4 = &DAT_004b52f0 + iVar3;
      if (*piVar4 < param_2[iVar3]) {
        piVar4 = param_2 + iVar3;
      }
      *piVar2 = *piVar4;
    }
    if ((uVar1 & 2) != 0) {
      piVar4 = &DAT_004b5140 + iVar3;
      if (*piVar4 < param_2[iVar3]) {
        piVar4 = param_2 + iVar3;
      }
      *piVar2 = *piVar4;
    }
    if ((uVar1 & 8) != 0) {
      piVar4 = &DAT_004b51d0 + iVar3;
      if (*piVar4 < param_2[iVar3]) {
        piVar4 = param_2 + iVar3;
      }
      *piVar2 = *piVar4;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x24);
  return;
}

