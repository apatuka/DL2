// FUN_0041be6c @ 0041be6c size=64 sig=undefined FUN_0041be6c() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_0041b71c

undefined4 FUN_0041be6c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_2 == 3) {
    FUN_0041b71c(param_1);
    FUN_004a43da(param_1,3,param_3,param_4);
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

