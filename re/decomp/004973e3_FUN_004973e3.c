// FUN_004973e3 @ 004973e3 size=123 sig=undefined FUN_004973e3() cc=unknown
// callers: FUN_00497460,FUN_004973e3
// callees: FUN_00497144,FUN_004973e3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char * FUN_004973e3(char *param_1,undefined4 param_2)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  
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
    pcVar3 = pcVar1;
    if (*pcVar1 == '\0') {
      pcVar1 = (char *)0x0;
    }
    else {
      while (((*pcVar3 == ' ' || (*pcVar3 == '\t')) ||
             (iVar2 = FUN_00497144(*pcVar3,param_2), iVar2 != 0))) {
        pcVar3 = pcVar3 + 1;
      }
      if ((*pcVar3 == '\r') || (*pcVar3 == '#')) {
        pcVar1 = (char *)FUN_004973e3(pcVar3,param_2);
      }
    }
  }
  return pcVar1;
}

