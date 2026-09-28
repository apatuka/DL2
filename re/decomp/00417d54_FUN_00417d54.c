// FUN_00417d54 @ 00417d54 size=114 sig=undefined FUN_00417d54() cc=unknown
// callers: CheckArmy
// callees: FUN_00476f24,FUN_004471c0

void FUN_00417d54(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  if (DAT_004b76b8 == '\0') {
    FUN_00476f24(DAT_004b76bc,0);
  }
  else {
    iVar2 = 0;
    piVar4 = &DAT_005332d8;
    do {
      iVar3 = 0;
      piVar1 = piVar4;
      do {
        if (*piVar1 == 1) {
          FUN_00476f24(piVar1[1],0);
        }
        iVar3 = iVar3 + 1;
        piVar1 = piVar1 + 8;
      } while (iVar3 < 10);
      iVar2 = iVar2 + 1;
      piVar4 = (int *)((int)piVar4 + 0x146);
    } while (iVar2 < 100);
  }
  if (DAT_004d5aa0 != '\0') {
    FUN_004471c0(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  }
  return;
}

