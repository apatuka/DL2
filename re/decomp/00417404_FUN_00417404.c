// FUN_00417404 @ 00417404 size=46 sig=undefined FUN_00417404() cc=unknown
// callers: FUN_004197dc,FUN_00419684
// callees: 

int FUN_00417404(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar2 = 0;
  piVar4 = &DAT_005332d8;
  do {
    iVar3 = 0;
    piVar1 = piVar4;
    do {
      if (*piVar1 == 1) {
        return iVar2;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar3 < 10);
    iVar2 = iVar2 + 1;
    piVar4 = (int *)((int)piVar4 + 0x146);
  } while (iVar2 < 100);
  return 0;
}

