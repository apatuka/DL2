// FUN_00450efc @ 00450efc size=59 sig=undefined FUN_00450efc() cc=unknown
// callers: FUN_00455a04
// callees: 

undefined4 FUN_00450efc(int param_1)

{
  undefined4 uVar1;
  
  if (((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') &&
     (((int)DAT_004fc02a & 1 << (*(byte *)(param_1 + 8) & 0x1f)) != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

