// FUN_004aca30 @ 004aca30 size=64 sig=undefined FUN_004aca30() cc=unknown
// callers: FUN_004acfa4
// callees: 

int FUN_004aca30(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  for (piVar2 = &DAT_00520198; (iVar1 < DAT_00520194 && (*piVar2 != 0)); piVar2 = piVar2 + 1) {
    iVar1 = iVar1 + 1;
  }
  if (iVar1 == DAT_00520194) {
    return -1;
  }
  (&DAT_00520198)[iVar1] = param_2;
  *(undefined4 *)(&DAT_0069f484 + iVar1 * 4) = param_1;
  return iVar1;
}

