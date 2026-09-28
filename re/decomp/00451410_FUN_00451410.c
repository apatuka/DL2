// FUN_00451410 @ 00451410 size=248 sig=undefined FUN_00451410() cc=unknown
// callers: FUN_004566c4,FUN_00456e44,FUN_00453350,FUN_004568c8
// callees: memset,FUN_004480a8,FUN_004511a4,FUN_00451180

void FUN_00451410(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  
  memset(&DAT_0057d310,0,0x510);
  for (iVar2 = *(int *)(DAT_0057cdf8 + 0x74); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x44)) {
    if ((*(char *)(iVar2 + 0x1d) != '\0') && ((&DAT_004faf87)[*(int *)(iVar2 + 4) * 0x24] == '\n'))
    {
      iVar5 = FUN_004480a8(iVar2);
      iVar3 = *(int *)(iVar2 + 0x20);
      iVar8 = iVar3 - iVar5;
      iVar4 = *(int *)(iVar2 + 0x24);
      iVar6 = iVar4 - iVar5;
      puVar1 = &DAT_0057d310 + iVar6 * 0x24;
      for (; iVar6 < iVar4 + iVar5; iVar6 = iVar6 + 1) {
        pcVar10 = puVar1 + iVar8 + 0x14d;
        for (iVar9 = iVar8; iVar9 < iVar3 + iVar5; iVar9 = iVar9 + 1) {
          iVar7 = FUN_004511a4(iVar9,iVar6);
          if ((iVar7 != 0) && (iVar7 = FUN_00451180(iVar2,iVar9,iVar6), iVar7 < iVar5)) {
            *pcVar10 = *pcVar10 + '\n';
          }
          pcVar10 = pcVar10 + 1;
        }
        puVar1 = puVar1 + 0x24;
      }
    }
  }
  return;
}

