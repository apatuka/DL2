// FUN_00495bf0 @ 00495bf0 size=97 sig=undefined FUN_00495bf0() cc=unknown
// callers: FUN_0049efae,FUN_0043acd4,FUN_0049f83e,FUN_0049f09b
// callees: 

void FUN_00495bf0(int *param_1,int *param_2)

{
  int iVar1;
  
  if ((param_2[1] < param_2[3]) && (*param_2 < param_2[2])) {
    if (*param_1 < *param_2) {
      *param_2 = *param_1;
    }
    if (param_2[2] < param_1[2]) {
      param_2[2] = param_1[2];
    }
    if (param_1[1] < param_2[1]) {
      param_2[1] = param_1[1];
    }
    if (param_2[3] < param_1[3]) {
      param_2[3] = param_1[3];
    }
  }
  else {
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

