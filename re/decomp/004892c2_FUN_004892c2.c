// FUN_004892c2 @ 004892c2 size=94 sig=undefined FUN_004892c2() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004892c2(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 0;
  uVar1 = 1;
  while( true ) {
    if (*param_1 == '\0') {
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      return uVar1;
    }
    if (((*param_1 < '!') || (*param_1 == '\x7f')) || (*param_1 == ',')) break;
    if ((*param_1 == '*') || (*param_1 == '?')) {
      uVar1 = 2;
    }
    if (((*param_1 == ':') || (*param_1 == '/')) || (*param_1 == '\\')) {
      iVar2 = 0;
    }
    else if (*param_1 != '.') {
      iVar2 = iVar2 + 1;
    }
    param_1 = param_1 + 1;
  }
  return 0;
}

