// FUN_0043e37c @ 0043e37c size=53 sig=undefined FUN_0043e37c() cc=unknown
// callers: CheckViewCombat
// callees: FUN_004a4025,FUN_0044a000,FUN_0043e024,FUN_004493dc

void FUN_0043e37c(void)

{
  FUN_0043e024();
  if (DAT_004c4950 != 0) {
    FUN_004a4025(DAT_004c4950);
    DAT_004c4950 = 0;
  }
  DAT_004d59b4 = DAT_00559dc4;
  FUN_004493dc(0);
  FUN_0044a000();
  return;
}

