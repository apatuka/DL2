// FUN_0048cc08 @ 0048cc08 size=367 sig=undefined FUN_0048cc08() cc=unknown
// callers: 
// callees: FUN_0048c2c5,FUN_0048c3f4,FUN_0048d03e

undefined4 FUN_0048cc08(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  int unaff_EBP;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 *puVar11;
  int *piVar12;
  
  iVar3 = *(int *)(unaff_EBP + 0xc);
  piVar1 = (int *)(unaff_EBP + -0x34);
  puVar9 = *(undefined4 **)(unaff_EBP + 0x10);
  puVar11 = (undefined4 *)(unaff_EBP + -0x24);
  for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar11 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar11 = puVar11 + 1;
  }
  piVar10 = *(int **)(unaff_EBP + 0x14);
  piVar12 = piVar1;
  for (iVar7 = 4; iVar7 != 0; iVar7 = iVar7 + -1) {
    *piVar12 = *piVar10;
    piVar10 = piVar10 + 1;
    piVar12 = piVar12 + 1;
  }
  if (*(int *)(unaff_EBP + -0x18) - *(int *)(unaff_EBP + -0x20) <
      *(int *)(unaff_EBP + -0x28) - *(int *)(unaff_EBP + -0x30)) {
    iVar7 = *(int *)(unaff_EBP + -0x18) - *(int *)(unaff_EBP + -0x20);
  }
  else {
    iVar7 = *(int *)(unaff_EBP + -0x28) - *(int *)(unaff_EBP + -0x30);
  }
  *(int *)(unaff_EBP + -4) = iVar7;
  if (*(int *)(unaff_EBP + -0x1c) - *(int *)(unaff_EBP + -0x24) <
      *(int *)(unaff_EBP + -0x2c) - *piVar1) {
    iVar7 = *(int *)(unaff_EBP + -0x1c) - *(int *)(unaff_EBP + -0x24);
  }
  else {
    iVar7 = *(int *)(unaff_EBP + -0x2c) - *piVar1;
  }
  if ((((iVar7 < 1) || (*(int *)(unaff_EBP + -4) < 1)) ||
      (*(int *)(*(int *)(unaff_EBP + 8) + 0xc) == -1)) || (*(int *)(iVar3 + 0xc) == -1)) {
    uVar5 = 2;
  }
  else {
    *(int *)(unaff_EBP + -0x1c) = *(int *)(unaff_EBP + -0x24) + iVar7;
    *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + -4);
    *(int *)(unaff_EBP + -0x2c) = *piVar1 + iVar7;
    *(int *)(unaff_EBP + -0x28) = *(int *)(unaff_EBP + -0x30) + *(int *)(unaff_EBP + -4);
    iVar6 = FUN_0048c2c5(iVar3);
    if (iVar6 != 0) {
      uVar5 = FUN_0048d03e(iVar3,*piVar1,*(undefined4 *)(unaff_EBP + -0x30));
      *(undefined4 *)(unaff_EBP + -0x10) = uVar5;
      iVar6 = FUN_0048c2c5(*(undefined4 *)(unaff_EBP + 8));
      if (iVar6 != 0) {
        uVar5 = FUN_0048d03e(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + -0x24),
                             *(undefined4 *)(unaff_EBP + -0x20));
        *(undefined4 *)(unaff_EBP + -0xc) = uVar5;
        if (*(int *)(*(int *)(unaff_EBP + 8) + 0xc) == 0x10) {
          iVar7 = iVar7 * 2;
        }
        *(undefined4 *)(unaff_EBP + -8) = 0;
        if (*(int *)(unaff_EBP + -8) < *(int *)(unaff_EBP + -4)) {
          do {
            pcVar8 = *(char **)(unaff_EBP + -0xc);
            *(undefined4 *)(unaff_EBP + -0x14) = *(undefined4 *)(unaff_EBP + -0x10);
            iVar6 = 0;
            if (0 < iVar7) {
              do {
                cVar2 = *pcVar8;
                pcVar8 = pcVar8 + 1;
                pcVar4 = *(char **)(unaff_EBP + -0x14);
                *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 1;
                if (cVar2 != *pcVar4) {
                  FUN_0048c3f4(*(undefined4 *)(unaff_EBP + 8));
                  FUN_0048c3f4(iVar3);
                  return 0;
                }
                iVar6 = iVar6 + 1;
              } while (iVar6 < iVar7);
            }
            *(int *)(unaff_EBP + -0xc) =
                 *(int *)(unaff_EBP + -0xc) + *(int *)(*(int *)(unaff_EBP + 8) + 0x10);
            *(int *)(unaff_EBP + -0x10) = *(int *)(unaff_EBP + -0x10) + *(int *)(iVar3 + 0x10);
            *(int *)(unaff_EBP + -8) = *(int *)(unaff_EBP + -8) + 1;
          } while (*(int *)(unaff_EBP + -8) < *(int *)(unaff_EBP + -4));
        }
        FUN_0048c3f4(*(undefined4 *)(unaff_EBP + 8));
      }
      FUN_0048c3f4(iVar3);
    }
    uVar5 = 1;
  }
  return uVar5;
}

