// FUN_0049716d @ 0049716d size=101 sig=undefined FUN_0049716d() cc=unknown
// callers: FUN_004977e9,FUN_004971d4,FUN_004975a1,FUN_004976dc,FUN_004978f7,FUN_00497784,FUN_004977bb,FUN_00497956,FUN_0049716d
// callees: FUN_0049716d

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_0049716d(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  if (param_1 == (char *)0x0) {
    pcVar1 = (char *)0x0;
  }
  else {
    do {
      for (; (*param_1 != '\r' && (*param_1 != '\0')); param_1 = param_1 + 1) {
      }
      pcVar1 = param_1;
      if ((*param_1 != '\0') && (pcVar1 = param_1 + 1, *pcVar1 == '\n')) {
        pcVar1 = param_1 + 2;
      }
      _DAT_0065edf0 = _DAT_0065edf0 + 1;
      param_1 = pcVar1;
    } while (*pcVar1 == '\r');
    pcVar2 = pcVar1;
    if (*pcVar1 == '\0') {
      pcVar1 = (char *)0x0;
    }
    else {
      for (; ((*pcVar2 == ' ' || (*pcVar2 == '\t')) || (*pcVar2 == '=')); pcVar2 = pcVar2 + 1) {
      }
      if ((*pcVar2 == '\r') || (*pcVar2 == '#')) {
        pcVar1 = (char *)FUN_0049716d(pcVar2);
      }
    }
  }
  return pcVar1;
}

