// FUN_00425620 @ 00425620 size=109 sig=undefined FUN_00425620() cc=unknown
// callers: FUN_00425ac4
// callees: Timer_Init,FUN_00412584,FUN_004253d8

undefined4 FUN_00425620(void)

{
  int iVar1;
  
  if (DAT_004b7d00 != 0) {
    return 1;
  }
  iVar1 = Timer_Init(DAT_004b7cf8);
  if (iVar1 != 0) {
    FUN_00412584(DAT_004b7cf8,3);
    DAT_004b7cf8 = 0;
    FUN_004253d8();
    return 1;
  }
  DAT_004c5b74 = 0xcf;
  DAT_004c5b70 = 0xc;
  DAT_004c5b7c = 0x197;
  DAT_004c5b78 = 0xd4;
  return 1;
}

