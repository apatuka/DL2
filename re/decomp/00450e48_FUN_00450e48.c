// FUN_00450e48 @ 00450e48 size=64 sig=undefined FUN_00450e48() cc=unknown
// callers: FUN_00455a04
// callees: 

undefined4 FUN_00450e48(int param_1)

{
  undefined4 uVar1;
  
  if ((((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] == '\x01') ||
      ((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] == '\x06')) &&
     ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] != '\n')) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

