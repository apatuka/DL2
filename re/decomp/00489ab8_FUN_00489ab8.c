// FUN_00489ab8 @ 00489ab8 size=41 sig=undefined FUN_00489ab8() cc=unknown
// callers: 
// callees: FUN_00495616

undefined4 FUN_00489ab8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00495616(param_1);
  if ((iVar1 == 0) || (param_1 == 0)) {
    uVar2 = 0;
  }
  else {
    (**(code **)(param_1 + 0x58))(param_1,2);
    uVar2 = 1;
  }
  return uVar2;
}

