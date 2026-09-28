// FUN_00495c95 @ 00495c95 size=47 sig=undefined FUN_00495c95() cc=unknown
// callers: 
// callees: 

void FUN_00495c95(int *param_1)

{
  int iVar1;
  
  if (param_1[2] < *param_1) {
    iVar1 = *param_1;
    *param_1 = param_1[2];
    param_1[2] = iVar1;
  }
  if (param_1[3] < param_1[1]) {
    iVar1 = param_1[1];
    param_1[1] = param_1[3];
    param_1[3] = iVar1;
  }
  return;
}

