// FUN_004899ca @ 004899ca size=51 sig=undefined FUN_004899ca() cc=unknown
// callers: 
// callees: FUN_0048960b,FUN_00495687

undefined4 FUN_004899ca(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x1c) == 0)) {
    uVar1 = 0;
  }
  else {
    FUN_0048960b(param_1);
    FUN_00495687(param_1);
    (**(code **)(param_1 + 0x88))(param_1);
    uVar1 = 1;
  }
  return uVar1;
}

