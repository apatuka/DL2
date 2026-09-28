// FUN_00495db5 @ 00495db5 size=44 sig=undefined FUN_00495db5() cc=unknown
// callers: FUN_004a60b1
// callees: 

undefined4 FUN_00495db5(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((((param_2 < *param_1) || (param_1[2] < param_2)) || (param_3 < param_1[1])) ||
     (param_1[3] < param_3)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

