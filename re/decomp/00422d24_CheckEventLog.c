// CheckEventLog @ 00422d24 size=533 sig=undefined CheckEventLog() cc=unknown
// callers: FUN_0044930c
// callees: FUN_00412f10,FUN_00412d38,FUN_00422bd8,FUN_00426594,DebugMessage,free,FUN_004a2cb5,FUN_004229f4,FUN_00412e94,FUN_004226a0
// strings: \"gpEventLog NULL in CheckEventLog()\"

/* auto-named from string evidence: CheckEventLog */

longlong CheckEventLog(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004b7b50 == 0) {
    DebugMessage(s_gpEventLog_NULL_in_CheckEventLog_004b7bb5);
    return (ulonglong)local_4 << 0x20;
  }
  if ((((DAT_004b7b58 != 0) && (DAT_004b7b64 == 0)) && (*(char *)(DAT_004b7b58 + 0x3c) == '\0')) &&
     (DAT_004b7b60 == 0)) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    FUN_00412f10(DAT_004b7b58);
    FUN_00412d38(DAT_004b7b58,*(undefined4 *)(DAT_004b7b50 + 0x3c));
    DAT_004b7b64 = 1;
    if (DAT_004b7b5c != 0) {
      free(DAT_004b7b5c);
      DAT_004b7b5c = 0;
    }
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  iVar1 = FUN_004a2cb5(DAT_004b7b50,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7b50 + 100) == 0)) {
    switch(local_4) {
    case 4:
      if (DAT_004d59b8 == '\0') {
        DAT_004d59b8 = '\x01';
        FUN_004229f4();
      }
      DAT_0053b8cc = DAT_0053b8cc != '\x01';
      FUN_00422bd8(0);
      DAT_004d59a4 = 0;
      break;
    case 0x11:
      FUN_00422bd8(0);
      DAT_004d59a4 = 0;
      break;
    case 0x12:
      FUN_00422bd8(1);
      DAT_004d59a4 = 0;
      break;
    case 0x13:
      FUN_00422bd8(2);
      DAT_004d59a4 = 0;
      break;
    case 0x14:
      FUN_00422bd8(3);
      DAT_004d59a4 = 0;
      break;
    case 0x15:
      FUN_00422bd8(4);
      DAT_004d59a4 = 0;
      break;
    case 0x16:
      FUN_00422bd8(5);
      DAT_004d59a4 = 0;
      break;
    case 0x17:
      if (DAT_004b7b58 != 0) {
        if (*(char *)(DAT_004b7b58 + 0x3c) != '\0') {
          FUN_00412e94(DAT_004b7b58);
        }
        FUN_00412f10(DAT_004b7b58);
        DAT_004b7b64 = 1;
      }
      DAT_004c5b78 = 0;
      DAT_004c5b70 = 0;
      DAT_004c5b7c = 0;
      DAT_004c5b74 = 0;
      FUN_00426594(&DAT_004d4b6c);
      break;
    case 0x18:
      FUN_004226a0();
      DAT_004d59a4 = 0;
    }
    return CONCAT44(local_4,1);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

