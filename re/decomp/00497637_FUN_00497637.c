// FUN_00497637 @ 00497637 size=96 sig=undefined FUN_00497637() cc=unknown
// callers: 
// callees: FUN_00497144

char * FUN_00497637(char *param_1,char *param_2,undefined4 param_3)

{
  int iVar1;
  char *pcVar2;
  
  if (param_1 == (char *)0x0) {
    *param_2 = '\0';
  }
  else {
    for (; (*param_1 == ' ' || (pcVar2 = param_1, *param_1 == '\t')); param_1 = param_1 + 1) {
    }
    while ((((*pcVar2 != ' ' && (*pcVar2 != '\t')) && (*pcVar2 != '\r')) &&
           ((*pcVar2 != '\0' && (iVar1 = FUN_00497144(*pcVar2,param_3), iVar1 == 0))))) {
      *param_2 = *pcVar2;
      param_2 = param_2 + 1;
      pcVar2 = pcVar2 + 1;
    }
    *param_2 = '\0';
  }
  return param_1;
}

