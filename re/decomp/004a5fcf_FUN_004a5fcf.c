// FUN_004a5fcf @ 004a5fcf size=226 sig=undefined FUN_004a5fcf() cc=unknown
// callers: 
// callees: FUN_0048f7f1

void FUN_004a5fcf(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  short sVar3;
  
  sVar3 = 0;
  while ((int)sVar3 < *(int *)(&DAT_0069f38c + param_1 * 4)) {
    iVar1 = param_1 * 0x140 + sVar3 * 0x10;
    piVar2 = (int *)(&DAT_0069f10c + iVar1);
    *(int *)(&DAT_0069f110 + iVar1) = *(int *)(&DAT_0069f110 + iVar1) + param_3;
    *(int *)(&DAT_0069f118 + iVar1) = *(int *)(&DAT_0069f118 + iVar1) + param_3;
    *piVar2 = *piVar2 + param_2;
    *(int *)(&DAT_0069f114 + iVar1) = *(int *)(&DAT_0069f114 + iVar1) + param_2;
    if ((((DAT_0069f0f4 < *piVar2) || (*(int *)(&DAT_0069f114 + iVar1) < DAT_0069f0ec)) ||
        (DAT_0069f0f8 < *(int *)(&DAT_0069f110 + iVar1))) ||
       (*(int *)(&DAT_0069f118 + iVar1) < DAT_0069f0f0)) {
      *(int *)(&DAT_0069f38c + param_1 * 4) = *(int *)(&DAT_0069f38c + param_1 * 4) + -1;
      if (0 < *(int *)(&DAT_0069f38c + param_1 * 4)) {
        FUN_0048f7f1(&DAT_0069f10c + param_1 * 0x140 + *(int *)(&DAT_0069f38c + param_1 * 4) * 0x10,
                     piVar2,0x10);
      }
    }
    else {
      if (*(int *)(&DAT_0069f110 + iVar1) < DAT_0069f0f0) {
        *(int *)(&DAT_0069f110 + iVar1) = DAT_0069f0f0;
      }
      if (DAT_0069f0f8 < *(int *)(&DAT_0069f118 + iVar1)) {
        *(int *)(&DAT_0069f118 + iVar1) = DAT_0069f0f8;
      }
      if (*piVar2 < DAT_0069f0ec) {
        *piVar2 = DAT_0069f0ec;
      }
      if (DAT_0069f0f4 < *(int *)(&DAT_0069f114 + iVar1)) {
        *(int *)(&DAT_0069f114 + iVar1) = DAT_0069f0f4;
      }
      sVar3 = sVar3 + 1;
    }
  }
  return;
}

