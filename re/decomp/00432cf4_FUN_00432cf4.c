// FUN_00432cf4 @ 00432cf4 size=60 sig=undefined FUN_00432cf4() cc=unknown
// callers: FUN_00434f28,CheckSubUnit,FUN_00431088,FUN_00432ad0,CheckSubRes,FUN_00449084,FUN_00435ed0,CheckSubInfo,CheckSubTech,FUN_00431128
// callees: FUN_00432cd0,FUN_00432cdc,FUN_00432ce8,FUN_00432cc4

void FUN_00432cf4(void)

{
  if ((DAT_004c42e4 == 0) || (*(char *)(DAT_004c42e4 + 0x3c) == '\0')) {
    if (DAT_00558d58 == 0) {
      FUN_00432cc4();
      return;
    }
    if (DAT_00558d58 == 1) {
      FUN_00432cd0();
      return;
    }
    if (DAT_00558d58 == 2) {
      FUN_00432cdc();
      return;
    }
    if (DAT_00558d58 != 3) {
      return;
    }
    FUN_00432ce8();
  }
  return;
}

