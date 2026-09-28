// FUN_00435ed0 @ 00435ed0 size=137 sig=undefined FUN_00435ed0() cc=unknown
// callers: FUN_0045e6d0
// callees: FUN_00432cf4,FUN_00430c38,FUN_004503f4,FUN_0044a000,FUN_00431088,FUN_0048db5d,FUN_00435e34,FUN_00432e0c,FUN_00430cd8

void FUN_00435ed0(void)

{
  int iVar1;
  
  if ((&DAT_005644f8)[DAT_0058f1f4 * 2] == 0) {
    iVar1 = FUN_004503f4(7,2,0xffffffff);
  }
  else {
    iVar1 = FUN_004503f4(7,0,0xffffffff);
    (&DAT_005644f8)[DAT_0058f1f4 * 2] = 0;
  }
  if (iVar1 == 0) {
    FUN_00430c38();
    FUN_00432cf4();
  }
  else {
    iVar1 = FUN_00430cd8(iVar1);
    if (iVar1 != 0) {
      FUN_00432cf4();
      FUN_0044a000();
      DAT_004d59a4 = 1;
      FUN_0048db5d(0);
      DAT_004d59a4 = 0;
      FUN_00431088();
    }
  }
  do {
    iVar1 = FUN_00435e34();
  } while (iVar1 == 0);
  FUN_00432e0c();
  return;
}

