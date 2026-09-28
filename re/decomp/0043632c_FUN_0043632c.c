// FUN_0043632c @ 0043632c size=204 sig=undefined FUN_0043632c() cc=unknown
// callers: FUN_004363f8
// callees: FUN_004362b4,FUN_0048db5d,FUN_0043611c,FUN_004a2cb5,FUN_00436184

longlong FUN_0043632c(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00436184();
  iVar1 = FUN_004a2cb5(DAT_004c465c,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c465c + 100) == 0)) {
    if (local_4 == 8) {
      FUN_0043611c();
      DAT_004d59a4 = 0;
      return (ulonglong)local_4 << 0x20;
    }
    if (((((local_4 == 4) || (local_4 == 5)) ||
         ((local_4 == 6 || ((local_4 == 7 || (local_4 == 9)))))) || (local_4 == 10)) ||
       (((local_4 == 0xb || (local_4 == 0xc)) || (local_4 == 0xd)))) {
      FUN_004362b4();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

