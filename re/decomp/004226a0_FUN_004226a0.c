// FUN_004226a0 @ 004226a0 size=236 sig=undefined FUN_004226a0() cc=unknown
// callers: CheckEventLog
// callees: FUN_00412f10,FUN_004a4025,FUN_004419c8,FUN_004229bc,FUN_004493dc,FUN_00412584,free,FUN_0044a000,FUN_00412e94,FUN_00422638,FUN_0043ca24,FUN_0045dfb0

void FUN_004226a0(void)

{
  char cVar1;
  int iVar2;
  
  FUN_004a4025(DAT_004b7b50);
  DAT_004b7b50 = 0;
  if (DAT_0053b8d0 != 0) {
    FUN_004419c8(DAT_0053b8d0);
    DAT_0053b8d0 = 0;
  }
  if (DAT_004b7b58 != 0) {
    if (*(char *)(DAT_004b7b58 + 0x3c) != '\0') {
      FUN_00412e94(DAT_004b7b58);
    }
    FUN_00412f10(DAT_004b7b58);
    FUN_00412584(DAT_004b7b58,3);
    DAT_004b7b58 = 0;
  }
  if (DAT_004b7b5c != 0) {
    free(DAT_004b7b5c);
    DAT_004b7b5c = 0;
  }
  DAT_004c5b78 = 0;
  DAT_004c5b70 = 0;
  DAT_004c5b7c = 0;
  DAT_004c5b74 = 0;
  DAT_004b7b40 = 0;
  DAT_004d59b4 = DAT_005574f0;
  DAT_004c5450 = DAT_0053b8d8;
  FUN_004493dc(0);
  FUN_0044a000();
  FUN_0045dfb0(6);
  cVar1 = FUN_00422638();
  if ((cVar1 != '\0') && (DAT_004b7b4c == '\0')) {
    iVar2 = FUN_004229bc();
    if (iVar2 == 0) {
      FUN_0043ca24();
      DAT_004b7b4c = '\x01';
    }
  }
  return;
}

