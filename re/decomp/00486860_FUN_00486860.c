// FUN_00486860 @ 00486860 size=173 sig=undefined FUN_00486860() cc=unknown
// callers: FUN_00480d78,FUN_00480b80
// callees: FUN_004865e8,FUN_004866fc

void FUN_00486860(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  for (iVar4 = 0; iVar4 < DAT_0065e028; iVar4 = iVar4 + 1) {
    piVar3 = &DAT_0065e02c + iVar4 * 7;
    piVar1 = &DAT_0065e03c + iVar4 * 7;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      iVar2 = (&DAT_0065e030)[iVar4 * 7];
      if (iVar2 == 1) {
        piVar1 = &DAT_0065e038 + iVar4 * 7;
        *piVar1 = *piVar1 + -1;
        if (*piVar1 < 0) {
          *piVar3 = *piVar3 + -6;
          (&DAT_0065e038)[iVar4 * 7] = 2;
        }
      }
      else if (iVar2 == 2) {
        (&DAT_0065e034)[iVar4 * 7] = (&DAT_0065e034)[iVar4 * 7] + 1;
        if (2 < (int)(&DAT_0065e034)[iVar4 * 7]) {
          *piVar3 = *piVar3 + 1;
          (&DAT_0065e034)[iVar4 * 7] = 0;
        }
      }
      else if (iVar2 == 4) {
        (&DAT_0065e038)[iVar4 * 7] = (&DAT_0065e038)[iVar4 * 7] + 1;
        if (2 < (int)(&DAT_0065e038)[iVar4 * 7]) {
          *piVar3 = *piVar3 + 6;
          (&DAT_0065e038)[iVar4 * 7] = 0;
        }
      }
      else if (iVar2 == 8) {
        piVar1 = &DAT_0065e034 + iVar4 * 7;
        *piVar1 = *piVar1 + -1;
        if (*piVar1 < 0) {
          *piVar3 = *piVar3 + -1;
          (&DAT_0065e034)[iVar4 * 7] = 2;
        }
      }
      (&DAT_0065e03c)[iVar4 * 7] = (&DAT_0065e040)[iVar4 * 7];
      if (((&DAT_0065e034)[iVar4 * 7] == 0) && ((&DAT_0065e038)[iVar4 * 7] == 0)) {
        FUN_004865e8(piVar3);
      }
      FUN_004866fc(piVar3);
    }
  }
  return;
}

