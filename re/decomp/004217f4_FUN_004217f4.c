// FUN_004217f4 @ 004217f4 size=51 sig=undefined FUN_004217f4() cc=unknown
// callers: FUN_00421828,FUN_00421878
// callees: FUN_0046b0e4

undefined4 FUN_004217f4(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x20) == DAT_0058f1f4) && (0 < *(short *)(param_1 + 0x30))) &&
     (iVar1 = FUN_0046b0e4(param_1), *(short *)(param_1 + 0x30) <= iVar1)) {
    return 1;
  }
  return 0;
}

