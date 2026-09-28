// FUN_004975a1 @ 004975a1 size=150 sig=undefined FUN_004975a1() cc=unknown
// callers: FUN_004956e2,FUN_004957b5
// callees: FUN_00497144,FUN_0049716d

char * FUN_004975a1(char *param_1,char *param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (param_1 == (char *)0x0) {
    *param_2 = '\0';
  }
  else {
    for (; (*param_1 == ' ' || (*param_1 == '\t')); param_1 = param_1 + 1) {
    }
    while (((param_1 != (char *)0x0 &&
            (((bVar1 || ((*param_1 != ' ' && (*param_1 != '\t')))) && (*param_1 != '\r')))) &&
           ((*param_1 != '\0' && (iVar2 = FUN_00497144(*param_1,param_3), iVar2 == 0))))) {
      if ((*param_1 == '\\') && ((param_1[1] == '\r' || (param_1[1] == '\n')))) {
        param_1 = (char *)FUN_0049716d(param_1);
      }
      else if (*param_1 == '\"') {
        param_1 = param_1 + 1;
        if (bVar1) break;
        bVar1 = true;
      }
      else {
        *param_2 = *param_1;
        param_1 = param_1 + 1;
        param_2 = param_2 + 1;
      }
    }
    *param_2 = '\0';
    if (*param_1 == '\0') {
      param_1 = (char *)0x0;
    }
  }
  return param_1;
}

