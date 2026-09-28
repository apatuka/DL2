// FUN_00463e04 @ 00463e04 size=28 sig=undefined FUN_00463e04() cc=unknown
// callers: FUN_00464b90,FUN_004442dc
// callees: 

int FUN_00463e04(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 1;
  piVar2 = &DAT_0058de50;
  do {
    if (*piVar2 == 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 7;
  } while (iVar1 < 10);
  return -1;
}

