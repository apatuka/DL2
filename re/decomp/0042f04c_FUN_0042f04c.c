// FUN_0042f04c @ 0042f04c size=119 sig=undefined FUN_0042f04c() cc=unknown
// callers: FUN_0042f0c4
// callees: FUN_0042ed64,FUN_0048db5d,FUN_004a2cb5

longlong FUN_0042f04c(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042ed64();
  iVar1 = FUN_004a2cb5(DAT_004c3800,&local_4);
  if ((((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c3800 + 100) == 0)) && (local_4 == 3)) {
    if (DAT_004c38e0 != 0) {
      DAT_004c38e0 = 0;
    }
    DAT_004d59a4 = 0;
    return 0x300000003;
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

