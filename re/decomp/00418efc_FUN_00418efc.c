// FUN_00418efc @ 00418efc size=62 sig=undefined FUN_00418efc() cc=unknown
// callers: 
// callees: FUN_00418e24,FUN_004a43da

undefined4 FUN_00418efc(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
  if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    if (param_4 != 0) {
      FUN_00418e24();
    }
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

