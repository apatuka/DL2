// FUN_0042c328 @ 0042c328 size=215 sig=undefined FUN_0042c328() cc=unknown
// callers: FUN_0042c41c
// callees: FUN_0048db5d,FUN_004a2cb5,FUN_0042c080,FUN_0042c1a4

longlong FUN_0042c328(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042c1a4();
  iVar1 = FUN_004a2cb5(DAT_004bdaf0,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004bdaf0 + 100) == 0)) {
    switch(local_4) {
    case 7:
      if (DAT_004d512c != 0) {
        FUN_0042c080(0);
      }
      break;
    case 8:
      if (DAT_004d512c != 1) {
        FUN_0042c080(1);
      }
      break;
    case 9:
      if (DAT_004d512c != 2) {
        FUN_0042c080(2);
      }
      break;
    case 10:
      if (DAT_004d512c != 3) {
        FUN_0042c080(3);
      }
      break;
    case 0xb:
      if (DAT_004d512c != 4) {
        FUN_0042c080(4);
      }
      break;
    case 0xc:
    case 0xd:
      return CONCAT44(local_4,local_4);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

