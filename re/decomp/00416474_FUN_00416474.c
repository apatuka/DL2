// FUN_00416474 @ 00416474 size=115 sig=undefined FUN_00416474() cc=unknown
// callers: FUN_004164e8
// callees: FUN_00426594,FUN_004a2cb5,FUN_004158f0,FUN_0048db5d

longlong FUN_00416474(void)

{
  int iVar1;
  uint local_8;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar1 = FUN_004a2cb5(DAT_004b7084,&local_8);
  FUN_004158f0();
  DAT_004d59a4 = 0;
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b7084 + 100) == 0)) {
    if (local_8 == 2) {
      return 0x200000001;
    }
    if (local_8 == 3) {
      FUN_00426594(&DAT_004d2628);
    }
  }
  return (ulonglong)local_8 << 0x20;
}

