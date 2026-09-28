// FUN_00480b80 @ 00480b80 size=94 sig=undefined FUN_00480b80() cc=unknown
// callers: FUN_0045f17c
// callees: FUN_0048d2e7,FUN_004451cc,FUN_00445270,FUN_004879fc,InvalidateRect,FUN_004450e0,FUN_00480150,FUN_00486860,FUN_00463da8,FUN_0048d32c

void FUN_00480b80(void)

{
  FUN_004450e0();
  FUN_00463da8(1);
  FUN_0048d2e7(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
  FUN_004451cc();
  FUN_00486860();
  FUN_00445270(1);
  FUN_00480150();
  InvalidateRect(DAT_004d5974,(RECT *)&DAT_00561a20,0);
  FUN_004879fc();
  FUN_0048d32c();
  return;
}

