// FUN_004196e4 @ 004196e4 size=41 sig=undefined FUN_004196e4() cc=unknown
// callers: FUN_00419924,CheckArmy,FUN_004198e0,FUN_0041a14c,FUN_00419c08,FUN_00419710
// callees: FUN_004a4025,FUN_0044a000

void FUN_004196e4(void)

{
  if (DAT_005332b0 != '\0') {
    FUN_004a4025(DAT_004b76b4);
    DAT_004b76b4 = 0;
  }
  DAT_005332b0 = 0;
  FUN_0044a000();
  return;
}

