// FUN_00426cd8 @ 00426cd8 size=121 sig=undefined FUN_00426cd8() cc=unknown
// callers: SelectInit,FUN_00426d54
// callees: FUN_00426c90,FUN_0045dfb0,FUN_00426bd0

void FUN_00426cd8(void)

{
  DAT_00557790 = 0xffffffff;
  FUN_0045dfb0(6);
  if (DAT_004d5aa0 == '\0') {
    FUN_00426bd0(0);
  }
  else {
    FUN_00426bd0(1);
  }
  DAT_00557790 = FUN_00426c90();
  if (DAT_00557790 == -1) {
    FUN_0045dfb0(6);
    FUN_00426bd0(1);
    DAT_00557790 = FUN_00426c90();
  }
  if (DAT_00557790 != -1) {
    (&DAT_005a43ec)[DAT_00557790 * 0x2b7] = (&DAT_005a43ec)[DAT_00557790 * 0x2b7] | 2;
  }
  return;
}

