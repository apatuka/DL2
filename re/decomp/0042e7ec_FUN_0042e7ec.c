// FUN_0042e7ec @ 0042e7ec size=179 sig=undefined FUN_0042e7ec() cc=unknown
// callers: FUN_0042e8a0
// callees: FUN_0049eb44,FUN_0048db5d,FUN_0042e694,FUN_004a2cb5,FUN_004a6b48

int FUN_0042e7ec(void)

{
  int iVar1;
  int local_68;
  undefined1 local_64 [100];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042e694();
  iVar1 = FUN_004a2cb5(DAT_004c3730,&local_68);
  if (((iVar1 == 0) && (local_68 != 0)) && (*(int *)(DAT_004c3730 + 100) == 0)) {
    if (local_68 == 5) {
      FUN_0049eb44(DAT_004c3730,4,1,0xe,99,local_64);
      FUN_004a6b48(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,local_64,0x18);
      DAT_004d59a4 = 0;
      return local_68;
    }
    if (local_68 == 6) {
      DAT_004d59a4 = 0;
      return 6;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

