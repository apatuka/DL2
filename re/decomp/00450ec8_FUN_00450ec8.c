// FUN_00450ec8 @ 00450ec8 size=51 sig=undefined FUN_00450ec8() cc=unknown
// callers: FUN_00455c88,FUN_00455a04
// callees: 

undefined4 FUN_00450ec8(int param_1)

{
  undefined4 uVar1;
  
  if (((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] == '\x03') &&
     ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] != '\t')) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

