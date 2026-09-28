// FUN_00495cc4 @ 00495cc4 size=93 sig=undefined FUN_00495cc4() cc=unknown
// callers: FUN_0049d7f4,FUN_0049ff48,FUN_0049ebfb,FUN_0048cd77,FUN_0048c85e
// callees: 

undefined4 FUN_00495cc4(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (param_1[1] < param_2[1]) {
    param_1[1] = param_2[1];
  }
  if (param_2[3] < param_1[3]) {
    param_1[3] = param_2[3];
  }
  if (*param_1 < *param_2) {
    *param_1 = *param_2;
  }
  if (param_2[2] < param_1[2]) {
    param_1[2] = param_2[2];
  }
  if (*param_1 < param_1[2]) {
    if (param_1[1] < param_1[3]) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

