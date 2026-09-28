// FUN_00494346 @ 00494346 size=101 sig=undefined FUN_00494346() cc=unknown
// callers: FUN_00494449,FUN_004943ab,FUN_0049483f
// callees: FUN_0048c28d,FUN_0048d13d

bool FUN_00494346(int param_1,int param_2)

{
  if ((((DAT_0065ecb8 == 0) || (*(int *)(DAT_0065ecb8 + 4) < param_1)) ||
      (*(int *)(DAT_0065ecb8 + 8) < param_2)) ||
     (*(int *)(DAT_0065ecb8 + 0xc) != *(int *)(DAT_0065ecac + 0xc))) {
    if (DAT_0065ecb8 != 0) {
      FUN_0048d13d(DAT_0065ecb8);
      DAT_0065ecb8 = 0;
    }
    DAT_0065ecb8 = FUN_0048c28d(param_1,param_2,*(undefined4 *)(DAT_0065ecac + 0xc));
  }
  return DAT_0065ecb8 != 0;
}

