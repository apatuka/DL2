// FUN_004b2500 @ 004b2500 size=31 sig=undefined FUN_004b2500() cc=unknown
// callers: FUN_004b26cc,FUN_004b2780
// callees: 

int FUN_004b2500(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_00521460;
  do {
    if (param_1 == *piVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 10);
  return -1;
}

