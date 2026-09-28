// FUN_0047dd24 @ 0047dd24 size=50 sig=undefined FUN_0047dd24() cc=unknown
// callers: FUN_0046e730
// callees: FUN_0047dce0,FUN_0047db84

void FUN_0047dd24(void)

{
  undefined4 *puVar1;
  
  FUN_0047dce0();
  for (puVar1 = &DAT_005a4eac; puVar1 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar1 = puVar1 + 0x2b7) {
    FUN_0047db84(puVar1);
  }
  return;
}

