// FUN_0041e81c @ 0041e81c size=179 sig=undefined FUN_0041e81c() cc=unknown
// callers: FUN_00462348
// callees: FUN_004a26e8,FUN_0048db5d,FUN_0041e674,FUN_00426594,FUN_004a2cb5,FUN_00475344

longlong FUN_0041e81c(void)

{
  int iVar1;
  uint in_ECX;
  uint local_4;
  
  if (DAT_004b792c == 0) {
    return (ulonglong)in_ECX << 0x20;
  }
  if (DAT_004d8264 != 0) {
    return CONCAT44(in_ECX,5);
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  local_4 = in_ECX;
  FUN_0048db5d(0);
  if (DAT_004c36ac != 0) {
    FUN_004a26e8(DAT_004c36ac);
  }
  FUN_0041e674();
  iVar1 = FUN_004a2cb5(DAT_004b792c,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b792c + 100) == 0)) {
    if (local_4 == 5) {
      if (DAT_0058f1fc != 0) {
        FUN_00475344();
      }
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
    if (local_4 == 3) {
      FUN_00426594(&DAT_004d4bd8);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

