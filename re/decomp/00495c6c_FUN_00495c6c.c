// FUN_00495c6c @ 00495c6c size=41 sig=undefined FUN_00495c6c() cc=unknown
// callers: FUN_0049ff48,FUN_00496cc3
// callees: 

undefined4 FUN_00495c6c(int *param_1)

{
  undefined4 uVar1;
  
  if (*param_1 < param_1[2]) {
    if (param_1[1] < param_1[3]) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

