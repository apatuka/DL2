// FUN_00495616 @ 00495616 size=31 sig=undefined FUN_00495616() cc=unknown
// callers: FUN_00489ab8
// callees: 

undefined4 FUN_00495616(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 4) == 3) || (*(int *)(param_1 + 4) == 1)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

