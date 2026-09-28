// FUN_0041140c @ 0041140c size=226 sig=undefined FUN_0041140c() cc=unknown
// callers: FUN_00411534
// callees: FUN_004b0a30,FUN_004b0b44

undefined4 FUN_0041140c(void)

{
  uint uVar1;
  
  DAT_005331b2 = FUN_004b0b44(0x4000);
  if (DAT_005331b2 == 0) {
    return 0;
  }
  for (DAT_005331ae = 32000; 0x4411 < DAT_005331ae; DAT_005331ae = DAT_005331ae - 4000) {
    DAT_005331b6 = FUN_004b0b44(DAT_005331ae << 2);
    if (DAT_005331b6 != 0) {
      DAT_0053319e = FUN_004b0b44(DAT_005331ae);
      if (DAT_0053319e != 0) break;
      FUN_004b0a30(DAT_005331b6);
    }
  }
  if (DAT_0053319e == 0) {
    return 0;
  }
  uVar1 = 0;
  do {
    *(undefined4 *)(DAT_005331b2 + uVar1 * 4) = 0xffffffff;
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x1000);
  for (uVar1 = 0; uVar1 < DAT_005331ae; uVar1 = uVar1 + 1) {
    *(undefined4 *)(DAT_005331b6 + uVar1 * 4) = 0xffffffff;
  }
  DAT_005331aa = 0;
  DAT_005331a2 = 0;
  DAT_005331a6 = 0;
  DAT_005331d8 = 1;
  DAT_005331cc = 0;
  return 1;
}

