// FUN_0048997c @ 0048997c size=78 sig=undefined FUN_0048997c() cc=unknown
// callers: 
// callees: FUN_0048960b,FUN_0048992c,FUN_00495687,_SmackWait@4

undefined4 FUN_0048997c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((param_1 == 0) || (*(undefined4 **)(param_1 + 0x1c) == (undefined4 *)0x0)) ||
     (*(int *)(param_1 + 4) != 3)) {
    uVar2 = 0;
  }
  else {
    iVar1 = _SmackWait_4(**(undefined4 **)(param_1 + 0x1c));
    if (iVar1 == 0) {
      FUN_0048960b(param_1);
      iVar1 = FUN_00495687(param_1);
      if (iVar1 != 0) {
        (**(code **)(param_1 + 0x88))(param_1);
      }
      FUN_0048992c(param_1);
    }
    uVar2 = 1;
  }
  return uVar2;
}

