// FUN_00494fb6 @ 00494fb6 size=99 sig=undefined FUN_00494fb6() cc=unknown
// callers: FUN_004152c0
// callees: FUN_00494b06,FUN_0048d13d,FUN_00494f0f

undefined4 FUN_00494fb6(void)

{
  if (DAT_0051dc9c != 0) {
    FUN_00494b06();
    FUN_00494f0f();
    if (DAT_0065ecbc != 0) {
      FUN_0048d13d(DAT_0065ecbc);
      DAT_0065ecbc = 0;
    }
    if (DAT_0065ecb8 != 0) {
      FUN_0048d13d(DAT_0065ecb8);
      DAT_0065ecb8 = 0;
    }
    DAT_0051dc9c = 0;
    DAT_0065ec7c = 0;
  }
  return 1;
}

