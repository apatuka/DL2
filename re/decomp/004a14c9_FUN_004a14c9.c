// FUN_004a14c9 @ 004a14c9 size=108 sig=undefined FUN_004a14c9() cc=unknown
// callers: FUN_00482940,FUN_004a4273
// callees: FUN_004a1457

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004a14c9(byte *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (byte *)0x0) {
    uVar1 = 0;
  }
  else {
    if ((*param_1 & 1) != 0) {
      DAT_0069eea0 = *(int *)(param_1 + 4);
    }
    if ((*param_1 & 2) != 0) {
      _DAT_0069eea4 = *(undefined4 *)(param_1 + 8);
    }
    if ((*param_1 & 4) != 0) {
      _DAT_0069eea8 = *(undefined4 *)(param_1 + 0xc);
    }
    if ((*param_1 & 8) != 0) {
      _DAT_0069eeac = *(undefined4 *)(param_1 + 0x10);
    }
    if ((*param_1 & 0x10) != 0) {
      _DAT_0069eeb0 = *(undefined4 *)(param_1 + 0x14);
    }
    if (DAT_0069eea0 != 1) {
      FUN_004a1457(0);
    }
    uVar1 = 1;
  }
  return uVar1;
}

