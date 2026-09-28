// FUN_00416df4 @ 00416df4 size=41 sig=undefined FUN_00416df4() cc=unknown
// callers: FUN_00416e70
// callees: 

undefined4 FUN_00416df4(int param_1)

{
  undefined4 uVar1;
  
  if ((*(char *)(param_1 + 6) == '\x1f') && (*(int *)(*(int *)(param_1 + 0x3c) + 0x8ac) != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

