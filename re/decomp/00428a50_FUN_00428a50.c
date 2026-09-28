// FUN_00428a50 @ 00428a50 size=209 sig=undefined FUN_00428a50() cc=unknown
// callers: FUN_00428b48
// callees: FUN_0048db5d,FUN_00428860,FUN_004a2cb5,FUN_00426594

longlong FUN_00428a50(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00428860();
  iVar1 = FUN_004a2cb5(DAT_004b7e0c,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7e0c + 100) == 0)) {
    switch(local_4) {
    case 3:
    case 4:
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 5:
      FUN_00426594(&DAT_004d4d64);
      break;
    case 6:
      DAT_004d5a4c = 0;
      break;
    case 7:
      DAT_004d5a4c = 1;
      break;
    case 8:
      DAT_004d5a50 = 8;
      break;
    case 9:
      DAT_004d5a50 = 4;
      break;
    case 10:
      DAT_004d5a50 = 1;
      break;
    case 0xb:
      DAT_004d5a50 = 2;
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

