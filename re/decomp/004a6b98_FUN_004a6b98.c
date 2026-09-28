// FUN_004a6b98 @ 004a6b98 size=93 sig=undefined FUN_004a6b98() cc=unknown
// callers: FUN_00411a68
// callees: FUN_004addb4

int FUN_004a6b98(char *param_1,char *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  while( true ) {
    iVar1 = FUN_004addb4((int)*param_1);
    iVar2 = FUN_004addb4((int)*param_2);
    if (((iVar1 != iVar2) || (*param_1 == '\0')) || (param_3 == 0)) break;
    param_3 = param_3 + -1;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  }
  if (param_3 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_004addb4((int)*param_1);
    iVar1 = FUN_004addb4((int)*param_2);
    iVar2 = iVar2 - iVar1;
  }
  return iVar2;
}

