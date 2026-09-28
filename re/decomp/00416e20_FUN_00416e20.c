// FUN_00416e20 @ 00416e20 size=78 sig=undefined FUN_00416e20() cc=unknown
// callers: FUN_00485668,FUN_00416e70
// callees: 

undefined4 FUN_00416e20(int param_1)

{
  undefined4 uVar1;
  
  if (((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fc05c) == 0) ||
     (((*(char *)(param_1 + 6) != '\x19' || (*(char *)(*(int *)(param_1 + 0x3c) + 0x21) == '\0')) &&
      ((*(char *)(param_1 + 6) != '\f' || (*(char *)(*(int *)(param_1 + 0x3c) + 0x21) != '\0'))))))
  {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

