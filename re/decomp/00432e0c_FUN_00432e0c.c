// FUN_00432e0c @ 00432e0c size=185 sig=undefined FUN_00432e0c() cc=unknown
// callers: CheckSubUnit,FUN_00435ed0,CheckSubTech,CheckSubInfo
// callees: free,FUN_004493dc,FUN_0044a000,FUN_00432dd0,FUN_00412f10,FUN_00432dbc,FUN_00432de4,FUN_00412e94,FUN_00412584,FUN_00432df8

void FUN_00432e0c(void)

{
  if (DAT_00558d58 == 0) {
    FUN_00432dbc();
  }
  else if (DAT_00558d58 == 1) {
    FUN_00432dd0();
  }
  else if (DAT_00558d58 == 2) {
    FUN_00432df8();
  }
  else if (DAT_00558d58 == 3) {
    FUN_00432de4();
  }
  if (DAT_004c42e4 != 0) {
    if (*(char *)(DAT_004c42e4 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004c42e4);
    }
    FUN_00412f10(DAT_004c42e4);
    FUN_00412584(DAT_004c42e4,3);
    DAT_004c42e4 = 0;
  }
  if (DAT_004c42e8 != 0) {
    free(DAT_004c42e8);
    DAT_004c42e8 = 0;
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  DAT_004d59b4 = DAT_00558cd0;
  DAT_004c5450 = DAT_00558ccc;
  FUN_004493dc(0);
  FUN_0044a000();
  return;
}

