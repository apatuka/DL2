// FUN_00450fcc @ 00450fcc size=101 sig=undefined FUN_00450fcc() cc=unknown
// callers: FUN_00451034
// callees: 

undefined4 FUN_00450fcc(int param_1)

{
  undefined4 uVar1;
  
  if (((1 << (*(byte *)(param_1 + 0x1e) & 0x1f) & *(uint *)(*(int *)(DAT_0057cdf8 + 4) + 0x8a8)) ==
       0) && ((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] != '\x03')) {
    if ((*(int *)(param_1 + 0x20) < 0x12) &&
       (((-1 < *(int *)(param_1 + 0x20) && (*(int *)(param_1 + 0x24) < 0x12)) &&
        (-1 < *(int *)(param_1 + 0x24))))) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

