// FUN_004942d0 @ 004942d0 size=118 sig=undefined FUN_004942d0() cc=unknown
// callers: FUN_00494449
// callees: FUN_0048c28d,FUN_0048d13d

bool FUN_004942d0(int param_1,int param_2)

{
  if ((((DAT_0065ecbc == 0) || (*(int *)(DAT_0065ecbc + 4) < param_1 * 2)) ||
      (*(int *)(DAT_0065ecbc + 8) < param_2 * 2)) ||
     (*(int *)(DAT_0065ecbc + 0xc) != *(int *)(DAT_0065ecac + 0xc))) {
    if (DAT_0065ecbc != 0) {
      FUN_0048d13d(DAT_0065ecbc);
      DAT_0065ecbc = 0;
    }
    DAT_0065ecbc = FUN_0048c28d(param_1 * 2,param_2 * 2,*(undefined4 *)(DAT_0065ecac + 0xc));
  }
  return DAT_0065ecbc != 0;
}

