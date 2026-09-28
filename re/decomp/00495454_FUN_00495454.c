// FUN_00495454 @ 00495454 size=85 sig=undefined FUN_00495454() cc=unknown
// callers: FUN_00489ef5,FUN_004a41d0,FUN_0048a667,FUN_004a3b3c,FUN_004a3533,FUN_0049d105
// callees: 

void FUN_00495454(undefined4 *param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  if (param_3 == (int *)0x0) {
    if (param_1[1] == 0) {
      *param_1 = param_2;
      param_1[1] = param_2;
      *param_2 = 0;
      param_2[1] = 0;
    }
    else {
      *(int **)(param_1[1] + 4) = param_2;
      *param_2 = param_1[1];
      param_2[1] = 0;
      param_1[1] = param_2;
    }
  }
  else {
    param_2[1] = (int)param_3;
    iVar1 = *param_3;
    if (iVar1 != 0) {
      *(int **)(iVar1 + 4) = param_2;
    }
    *param_3 = (int)param_2;
    *param_2 = iVar1;
    if (param_3 == (int *)*param_1) {
      *param_1 = param_2;
    }
  }
  return;
}

