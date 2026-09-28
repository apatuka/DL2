// FUN_004835bc @ 004835bc size=67 sig=undefined FUN_004835bc() cc=unknown
// callers: LoadGlobalSprites,FUN_0046ce10,FUN_00483524
// callees: FUN_004845d4,FUN_004419c8,FUN_004835a8,FUN_0047e0a0,memset

void FUN_004835bc(void)

{
  FUN_004835a8(1);
  if (DAT_004dcf50 != 0) {
    FUN_004419c8(DAT_004dcf50);
    DAT_004dcf50 = 0;
  }
  memset(&DAT_00657e60,0x6b,0);
  FUN_0047e0a0();
  FUN_004845d4(0);
  FUN_004845d4(1);
  return;
}

