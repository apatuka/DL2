// FUN_0043cbf8 @ 0043cbf8 size=100 sig=undefined FUN_0043cbf8() cc=unknown
// callers: CheckTechTree
// callees: FUN_004839a4,FUN_00483cbc,FUN_00483a10,FUN_0043cb34,FUN_004764dc

void FUN_0043cbf8(void)

{
  DAT_00559db4 = FUN_004839a4(DAT_00559da8);
  FUN_00483a10(&DAT_00559da8,PTR_DAT_004d5988 + 0x3a);
  if (DAT_00559db4 == -1) {
    DAT_00559db4 = FUN_00483cbc(PTR_DAT_004d5988,0);
  }
  if (DAT_00559db4 != DAT_00559db0) {
    FUN_004764dc((int)(char)*PTR_DAT_004d5988,DAT_00559db4);
  }
  FUN_0043cb34();
  return;
}

