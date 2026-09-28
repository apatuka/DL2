// FUN_004954a9 @ 004954a9 size=80 sig=undefined FUN_004954a9() cc=unknown
// callers: FUN_00495560,FUN_004a41d0,FUN_0049d18d,FUN_004a4025,FUN_00495f8f,FUN_004a3f2e
// callees: 

void FUN_004954a9(int *param_1,int *param_2)

{
  int iVar1;
  
  if (param_2[1] == 0) {
    param_1[1] = *param_2;
  }
  else {
    iVar1 = *param_2;
    *(int *)param_2[1] = iVar1;
    if (iVar1 == 0) {
      *param_1 = param_2[1];
    }
  }
  if (*param_2 == 0) {
    *param_1 = param_2[1];
  }
  else {
    iVar1 = param_2[1];
    *(int *)(*param_2 + 4) = iVar1;
    if (iVar1 == 0) {
      param_1[1] = *param_2;
    }
  }
  param_2[1] = 0;
  *param_2 = 0;
  return;
}

