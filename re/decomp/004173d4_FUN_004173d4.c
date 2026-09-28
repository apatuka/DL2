// FUN_004173d4 @ 004173d4 size=47 sig=undefined FUN_004173d4() cc=unknown
// callers: FUN_00419924,FUN_00419710
// callees: 

int FUN_004173d4(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar2 = &DAT_005332d8;
  do {
    iVar3 = 0;
    piVar1 = piVar2;
    do {
      if (*piVar1 == 1) {
        return piVar1[1];
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar3 < 10);
    iVar4 = iVar4 + 1;
    piVar2 = (int *)((int)piVar2 + 0x146);
  } while (iVar4 < 100);
  return 0;
}

