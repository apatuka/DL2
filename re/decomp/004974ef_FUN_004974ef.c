// FUN_004974ef @ 004974ef size=80 sig=undefined FUN_004974ef() cc=unknown
// callers: FUN_004978bf,FUN_004976dc,FUN_00497859,FUN_00497956
// callees: 

char * FUN_004974ef(char *param_1,char *param_2)

{
  char *pcVar1;
  
  if (param_1 == (char *)0x0) {
    *param_2 = '\0';
  }
  else {
    for (; ((*param_1 == ' ' || (*param_1 == '\t')) || (pcVar1 = param_1, *param_1 == '='));
        param_1 = param_1 + 1) {
    }
    for (; ((*pcVar1 != ' ' && (*pcVar1 != '=')) &&
           ((*pcVar1 != '\t' && ((*pcVar1 != '\r' && (*pcVar1 != '\0')))))); pcVar1 = pcVar1 + 1) {
      *param_2 = *pcVar1;
      param_2 = param_2 + 1;
    }
    *param_2 = '\0';
  }
  return param_1;
}

