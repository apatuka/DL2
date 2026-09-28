// FUN_00436864 @ 00436864 size=231 sig=undefined FUN_00436864() cc=unknown
// callers: FUN_0043694c
// callees: FUN_0048db5d,FUN_00436418,FUN_00436838,FUN_004a2cb5

longlong FUN_00436864(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00436418();
  iVar1 = FUN_004a2cb5(DAT_004c4660,&local_4);
  if ((((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c4660 + 100) == 0)) &&
     ((((local_4 == 2 || (local_4 == 3)) || ((local_4 == 4 || ((local_4 == 5 || (local_4 == 6))))))
      || ((local_4 == 8 ||
          ((((((local_4 == 9 || (local_4 == 10)) || (local_4 == 0xb)) ||
             ((local_4 == 0xc || (local_4 == 0xe)))) ||
            ((local_4 == 0xd || ((local_4 == 0xf || (local_4 == 0x10)))))) || (local_4 == 0x11))))))
     )) {
    FUN_00436838();
    DAT_004d59a4 = 0;
    return CONCAT44(local_4,local_4);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

