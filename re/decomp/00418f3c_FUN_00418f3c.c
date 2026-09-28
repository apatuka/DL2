// FUN_00418f3c @ 00418f3c size=56 sig=undefined FUN_00418f3c() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_00418e90

undefined4 FUN_00418f3c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    FUN_00418e90();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

