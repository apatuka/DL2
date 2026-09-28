// FUN_0042f5d8 @ 0042f5d8 size=167 sig=undefined FUN_0042f5d8() cc=unknown
// callers: FUN_0044930c
// callees: DebugMessage,FUN_0042f554,FUN_004a2cb5,FUN_00426594,FUN_0042f5ac
// strings: \"gpSelectPort NULL in gpSelectPort\"

longlong FUN_0042f5d8(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004c4220 == 0) {
    DebugMessage(s_gpSelectPort_NULL_in_gpSelectPor_004c4235);
    return (ulonglong)local_4 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  iVar1 = FUN_004a2cb5(DAT_004c4220,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c4220 + 100) == 0)) {
    if (local_4 == 5) {
      FUN_00426594(&DAT_004d37bc);
      DAT_004d59a4 = 0;
    }
    else if (local_4 == 6) {
      FUN_0042f5ac();
      DAT_004d59a4 = 0;
    }
    else if (local_4 == 7) {
      FUN_0042f5ac();
      DAT_004d59a4 = 0;
    }
    return CONCAT44(local_4,1);
  }
  FUN_0042f554();
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

