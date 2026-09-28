// FUN_00403684 @ 00403684 size=204 sig=undefined FUN_00403684() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00403350,FUN_0046ca40

void FUN_00403684(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  
  iVar8 = 0;
  piVar9 = &DAT_0055a804;
  piVar7 = (int *)(&DAT_005220a4 + param_1 * 0x1c);
  do {
    if (((1 << ((byte)iVar8 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) != 0) && (8 < *piVar7)
       ) {
      iVar1 = *piVar7;
      iVar2 = *piVar9;
      iVar3 = (&DAT_0055a804)[param_1];
      iVar4 = *piVar9;
      iVar5 = (&DAT_0055a804)[param_1];
      uVar6 = FUN_0046ca40();
      if ((int)(uVar6 % 100) <
          ((0x32 - iVar1) * 0x32) / 0x2a + ((iVar2 - iVar3) * 0x32) / (iVar4 + iVar5)) {
        FUN_00403350(param_1,iVar8);
      }
    }
    iVar8 = iVar8 + 1;
    piVar9 = piVar9 + 1;
    piVar7 = piVar7 + 1;
  } while (iVar8 < 7);
  return;
}

