// FUN_00495d21 @ 00495d21 size=104 sig=undefined FUN_00495d21() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00495d21(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  if ((param_1[1] < param_2[3]) && (*param_1 < param_2[2])) {
    if (*param_2 < param_1[2]) {
      *param_2 = param_1[2];
    }
    if (*param_1 < param_2[2]) {
      param_2[2] = *param_1;
    }
    if (param_2[1] < param_1[3]) {
      param_2[1] = param_1[3];
    }
    if (param_1[1] < param_2[3]) {
      param_2[3] = param_1[1];
    }
  }
  if ((param_2[1] < param_2[3]) && (*param_2 < param_2[2])) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

