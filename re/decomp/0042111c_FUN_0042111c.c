// FUN_0042111c @ 0042111c size=53 sig=undefined FUN_0042111c() cc=unknown
// callers: FUN_00421178
// callees: 

int FUN_0042111c(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar2 = 0;
  iVar5 = 0;
  piVar4 = &DAT_004b7760;
  do {
    iVar3 = 0;
    piVar1 = piVar4;
    do {
      if (*piVar1 == 1) {
        iVar2 = iVar2 + 1;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar3 < 0xd);
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 0xd;
  } while (iVar5 < 4);
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  return iVar2;
}

