// FUN_00489159 @ 00489159 size=173 sig=undefined FUN_00489159() cc=unknown
// callers: FUN_00489232,FUN_00489159
// callees: FUN_004addb4,FUN_00489159

bool FUN_00489159(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  while( true ) {
    if (*param_2 == '\0') {
      return *param_1 == '\0';
    }
    if (*param_2 == '*') break;
    if (*param_2 == '?') {
      if (*param_1 == '\0') {
        return false;
      }
    }
    else {
      iVar2 = FUN_004addb4((int)*param_2);
      iVar3 = FUN_004addb4((int)*param_1);
      if (iVar2 != iVar3) {
        return false;
      }
    }
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  if (param_2[1] == '\0') {
    return true;
  }
  if ((param_2[1] == '.') && (param_2[2] == '\0')) {
    return true;
  }
  if (((param_2[1] == '.') && (param_2[2] == '*')) && (param_2[3] == '\0')) {
    return true;
  }
  while( true ) {
    if (*param_1 == '\0') {
      return false;
    }
    cVar1 = FUN_00489159(param_1,param_2 + 1);
    if (cVar1 != '\0') break;
    param_1 = param_1 + 1;
  }
  return true;
}

