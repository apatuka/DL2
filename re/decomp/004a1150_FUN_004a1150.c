// FUN_004a1150 @ 004a1150 size=58 sig=undefined FUN_004a1150() cc=unknown
// callers: FUN_0041f024,FUN_00425d68,FUN_0049eb44,FUN_004a19b4,FUN_0041ab54,FUN_00425bc4,FUN_004a1c75,FUN_004a43da,FUN_00438dbc,FUN_00438134,FUN_004a3f2e
// callees: FUN_004a110f,FUN_004a10d0

undefined4 FUN_004a1150(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    if (param_3 == 0) {
      uVar1 = FUN_004a110f(param_1,param_2);
      return uVar1;
    }
    if (param_3 == 1) {
      uVar1 = FUN_004a10d0(param_1,param_2);
      return uVar1;
    }
    if (param_3 == 2) {
      return param_2;
    }
  }
  return 0;
}

