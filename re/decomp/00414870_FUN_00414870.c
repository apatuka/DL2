// FUN_00414870 @ 00414870 size=123 sig=undefined FUN_00414870() cc=unknown
// callers: FUN_004148ec,FUN_0044930c
// callees: FUN_004144a8,FUN_004a2cb5,FUN_00414004,FUN_0048db5d

longlong FUN_00414870(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004144a8();
  iVar1 = FUN_004a2cb5(DAT_004b7054,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7054 + 100) == 0)) {
    if (local_4 == 3) {
      DAT_004d59a4 = 0;
      FUN_00414004();
      return CONCAT44(local_4,local_4);
    }
    if (local_4 == 4) {
      DAT_004d59a4 = 0;
      return 0x400000004;
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

