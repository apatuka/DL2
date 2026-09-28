// FUN_00411148 @ 00411148 size=162 sig=undefined FUN_00411148() cc=unknown
// callers: FUN_004111ec
// callees: FUN_00410ed8,FUN_00411124

void FUN_00411148(int param_1)

{
  uint uVar1;
  
  DAT_005331e0 = DAT_005331e0 + param_1;
  while (param_1 != 0) {
    *(undefined4 *)(DAT_005331b6 + DAT_005331a2 * 4) =
         *(undefined4 *)(DAT_005331b2 + (uint)DAT_005331ba * 4);
    uVar1 = DAT_005331a2;
    *(uint *)(DAT_005331b2 + (uint)DAT_005331ba * 4) = DAT_005331a2;
    DAT_005331a2 = DAT_005331a2 + 1;
    FUN_00411124(CONCAT31((int3)(uVar1 >> 8),*(undefined1 *)(DAT_0053319e + 2 + DAT_005331a2)));
    param_1 = param_1 + -1;
  }
  if (DAT_005331a2 < 0x4000) {
    DAT_005331a6 = 0;
  }
  else {
    DAT_005331a6 = DAT_005331a2 - 0x3fff;
    if (DAT_005331ae - 0x12U <= DAT_005331a2) {
      FUN_00410ed8();
    }
  }
  return;
}

