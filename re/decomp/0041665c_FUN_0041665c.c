// FUN_0041665c @ 0041665c size=151 sig=undefined FUN_0041665c() cc=unknown
// callers: FUN_004166f4
// callees: FUN_0048db5d,FUN_0049eb44,FUN_00416518,FUN_004a2cb5

longlong FUN_0041665c(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00416518();
  iVar1 = FUN_004a2cb5(DAT_004b7688,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7688 + 100) == 0)) {
    if (local_4 == 5) {
      FUN_0049eb44(DAT_004b7688,4,1,0xe,DAT_005332a4,DAT_005332a0);
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
    if (local_4 == 6) {
      DAT_004d59a4 = 0;
      return 0x600000006;
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

