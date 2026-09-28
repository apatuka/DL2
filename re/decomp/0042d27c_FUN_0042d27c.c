// FUN_0042d27c @ 0042d27c size=133 sig=undefined FUN_0042d27c() cc=unknown
// callers: FUN_0042d3dc
// callees: FUN_004a4025,FUN_00412e94,FUN_00412f10,free,FUN_0044a000,FUN_004493dc,FUN_00412584

void FUN_0042d27c(void)

{
  FUN_004a4025(DAT_004bf8fc);
  DAT_004bf8fc = 0;
  DAT_004d59b4 = DAT_00557c14;
  FUN_004493dc(0);
  if (DAT_00557c48 != 0) {
    if (*(char *)(DAT_00557c48 + 0x3c) != '\0') {
      FUN_00412e94(DAT_00557c48);
    }
    FUN_00412f10(DAT_00557c48);
    FUN_00412584(DAT_00557c48,3);
  }
  if (DAT_00557c4c != 0) {
    free(DAT_00557c4c);
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  FUN_0044a000();
  return;
}

