// FUN_0041daa4 @ 0041daa4 size=105 sig=undefined FUN_0041daa4() cc=unknown
// callers: FUN_0041db10
// callees: FUN_0044c754

int FUN_0041daa4(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = 0;
  piVar2 = &DAT_004b7760;
  do {
    iVar3 = 0;
    piVar1 = piVar2;
    do {
      if (*piVar1 == 1) {
        iVar4 = iVar4 + 1;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar3 < 0xd);
    iVar5 = iVar5 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar5 < 4);
  if (iVar4 == 0) {
    if (DAT_0053b868 == 7) {
      iVar5 = FUN_0044c754(DAT_0053b84c);
      if (iVar5 != 0) {
        iVar4 = 1;
      }
    }
    else if (*(int *)(DAT_0053b850 + 0x10 + DAT_0053b868 * 4) != 0) {
      iVar4 = 1;
    }
  }
  return iVar4;
}

