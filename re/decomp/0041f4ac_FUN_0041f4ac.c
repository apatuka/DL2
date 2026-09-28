// FUN_0041f4ac @ 0041f4ac size=149 sig=undefined FUN_0041f4ac() cc=unknown
// callers: FUN_0041f740
// callees: FUN_00412584,FUN_0044a000,FUN_004493dc,free,FUN_00412e94,FUN_004a4025,FUN_00412f10

void FUN_0041f4ac(void)

{
  FUN_004a4025(DAT_004b7974);
  DAT_004b7974 = 0;
  DAT_004d59b4 = DAT_0053b884;
  FUN_004493dc(0);
  if (DAT_004b7988 != 0) {
    if (*(char *)(DAT_004b7988 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7988);
    }
    FUN_00412f10(DAT_004b7988);
    FUN_00412584(DAT_004b7988,3);
    DAT_004b7988 = 0;
  }
  if (DAT_004b798c != 0) {
    free(DAT_004b798c);
    DAT_004b798c = 0;
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  FUN_0044a000();
  return;
}

