// FUN_00415514 @ 00415514 size=115 sig=undefined FUN_00415514() cc=unknown
// callers: FUN_00415588
// callees: FUN_00426594,FUN_004a2cb5,FUN_0048db5d,FUN_004152f8

longlong FUN_00415514(void)

{
  int iVar1;
  uint local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar1 = FUN_004a2cb5(DAT_004b7074,&local_8);
  FUN_004152f8();
  DAT_004d59a4 = 0;
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b7074 + 100) == 0)) {
    if (local_8 == 2) {
      return 0x200000001;
    }
    if (local_8 == 3) {
      FUN_00426594(&DAT_004d2b80);
    }
  }
  return (ulonglong)local_8 << 0x20;
}

