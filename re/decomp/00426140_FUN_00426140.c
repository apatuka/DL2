// FUN_00426140 @ 00426140 size=249 sig=undefined FUN_00426140() cc=unknown
// callers: FUN_00426594
// callees: FUN_00412f10,FUN_004a4025,FUN_004493dc,FUN_004691f8,FUN_00412584,free,FUN_0044a000,FUN_0048c85e,FUN_00412e94

void FUN_00426140(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_0051dc18 = DAT_00557564;
  FUN_004a4025(DAT_004b7ce4);
  DAT_004b7ce4 = 0;
  DAT_004d59b4 = DAT_00557550;
  FUN_004493dc(0);
  if (DAT_004b7cf8 != 0) {
    if (*(char *)(DAT_004b7cf8 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7cf8);
    }
    FUN_00412f10(DAT_004b7cf8);
    FUN_00412584(DAT_004b7cf8,3);
    DAT_004b7cf8 = 0;
  }
  if (DAT_004b7cfc != 0) {
    free(DAT_004b7cfc);
    DAT_004b7cfc = 0;
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  if (DAT_004b7d04 != 0) {
    local_10 = 0;
    local_c = 0;
    local_4 = 0x1e0;
    local_8 = 0x280;
    FUN_0048c85e(DAT_004b7d04,DAT_004d5c28,&local_10,&local_10,&local_10,&local_10,0);
  }
  if (DAT_004d5978 == 0) {
    FUN_0044a000();
  }
  else {
    FUN_004691f8();
  }
  return;
}

