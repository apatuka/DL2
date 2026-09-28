// FUN_0046fa7c @ 0046fa7c size=102 sig=undefined FUN_0046fa7c() cc=unknown
// callers: WinMain
// callees: 

int FUN_0046fa7c(char *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  while ((*param_1 != '\0' && (iVar1 < param_3))) {
    while ((*param_1 != '\0' && (((&DAT_005209ce)[*param_1 * 2] & 8) != 0))) {
      param_1 = param_1 + 1;
    }
    if (*param_1 != '\0') {
      *param_2 = param_1;
      while ((*param_1 != '\0' && (((&DAT_005209ce)[*param_1 * 2] & 8) == 0))) {
        param_1 = param_1 + 1;
      }
      if (*param_1 != '\0') {
        *param_1 = '\0';
        param_1 = param_1 + 1;
      }
      iVar1 = iVar1 + 1;
      param_2 = param_2 + 1;
    }
  }
  return iVar1;
}

