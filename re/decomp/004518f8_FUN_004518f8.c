// FUN_004518f8 @ 004518f8 size=45 sig=undefined FUN_004518f8() cc=unknown
// callers: FUN_00451b68
// callees: FUN_00450de0

void FUN_004518f8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00450de0(param_1);
  if ((iVar1 == 0) && ((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] == '\x03')) {
    *(undefined1 *)(param_1 + 0x14) = 2;
  }
  return;
}

