// FUN_004251d8 @ 004251d8 size=143 sig=undefined FUN_004251d8() cc=unknown
// callers: FUN_00425364,FUN_00425268
// callees: FUN_00412f10,FUN_004a4025,FUN_004493dc,FUN_00412584,free,FUN_0044a000,FUN_00412e94

void FUN_004251d8(void)

{
  FUN_004a4025(DAT_004b7c80);
  DAT_004b7c80 = 0;
  DAT_004d59b4 = DAT_0055752c;
  FUN_004493dc(0);
  if (DAT_00557530 != 0) {
    if (*(char *)(DAT_00557530 + 0x3c) != '\0') {
      FUN_00412e94(DAT_00557530);
    }
    FUN_00412f10(DAT_00557530);
    FUN_00412584(DAT_00557530,3);
  }
  if ((DAT_00557540 != 0) && (DAT_0055754c == 0)) {
    free(DAT_00557540);
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  FUN_0044a000();
  return;
}

