// FUN_004b18ac @ 004b18ac size=97 sig=undefined FUN_004b18ac() cc=unknown
// callers: FUN_004b1fb4,FUN_004b1c1c
// callees: strlen,FUN_004b0118,FUN_004b232c,FUN_004b233c

int FUN_004b18ac(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = strlen(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    FUN_004b232c();
    for (piVar3 = DAT_0069f82c; *piVar3 != 0; piVar3 = piVar3 + 1) {
      iVar2 = FUN_004b0118(*piVar3,param_1,iVar1);
      if ((iVar2 == 0) && (*(char *)(*piVar3 + iVar1) == '=')) break;
    }
    FUN_004b233c();
    if (*piVar3 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = iVar1 + *piVar3 + 1;
    }
  }
  return iVar1;
}

