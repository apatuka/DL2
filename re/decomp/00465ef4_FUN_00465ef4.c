// FUN_00465ef4 @ 00465ef4 size=141 sig=undefined FUN_00465ef4() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00465ef4(char *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_10;
  
  piVar4 = &DAT_004d5070;
  local_10 = 0;
  piVar2 = &DAT_004d5060;
  while( true ) {
    iVar1 = *piVar2 + (int)*param_1;
    iVar3 = *piVar4 + (int)param_1[1];
    if ((((-1 < iVar1) && (-1 < iVar3)) && (iVar1 < DAT_004d5b1a)) &&
       ((iVar3 < DAT_004d5b1b && ((&DAT_005a0555)[iVar1 * 10 + iVar3 * 400] == '\0')))) break;
    local_10 = local_10 + 1;
    piVar4 = piVar4 + 1;
    piVar2 = piVar2 + 1;
    if (3 < local_10) {
      return 0;
    }
  }
  return 1;
}

