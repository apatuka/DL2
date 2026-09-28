// FUN_00495d89 @ 00495d89 size=44 sig=undefined FUN_00495d89() cc=unknown
// callers: FUN_0049f31e,FUN_0049c45d
// callees: 

undefined4 FUN_00495d89(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((((param_2 < *param_1) || (param_1[2] <= param_2)) || (param_3 < param_1[1])) ||
     (param_1[3] <= param_3)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

