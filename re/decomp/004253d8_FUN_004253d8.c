// FUN_004253d8 @ 004253d8 size=51 sig=undefined FUN_004253d8() cc=unknown
// callers: FUN_00425620,FUN_0042540c
// callees: FUN_004152ec,FUN_0049eb44,FUN_00425f04

void FUN_004253d8(void)

{
  if (DAT_004b7cf8 == 0) {
    FUN_0049eb44(DAT_004b7ce4,3,1,0x3c,1,2);
    FUN_004152ec();
    FUN_00425f04();
    DAT_004b7d00 = 1;
  }
  return;
}

