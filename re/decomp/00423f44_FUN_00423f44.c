// FUN_00423f44 @ 00423f44 size=107 sig=undefined FUN_00423f44() cc=unknown
// callers: FUN_00423fb0
// callees: FUN_00423dd8,FUN_004a2cb5,FUN_0048db5d

longlong FUN_00423f44(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00423dd8();
  iVar1 = FUN_004a2cb5(DAT_004b7c28,&local_4);
  if ((((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7c28 + 100) == 0)) && (local_4 - 3 < 5)
     ) {
    DAT_004d59a4 = 0;
    return CONCAT44(local_4,local_4);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

