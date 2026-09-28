// FUN_00450e28 @ 00450e28 size=32 sig=undefined FUN_00450e28() cc=unknown
// callers: FUN_00455c88,FUN_00454928,FUN_00455a04
// callees: 

undefined4 FUN_00450e28(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 4) == 0x14) || (*(int *)(param_1 + 4) == 0x22)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

