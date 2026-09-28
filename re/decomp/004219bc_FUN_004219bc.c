// FUN_004219bc @ 004219bc size=107 sig=undefined FUN_004219bc() cc=unknown
// callers: FUN_00421a28
// callees: FUN_004a2cb5,FUN_0048db5d,FUN_004218a4

longlong FUN_004219bc(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004218a4();
  iVar1 = FUN_004a2cb5(DAT_004b7b04,&local_4);
  if ((((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7b04 + 100) == 0)) && (local_4 - 3 < 3)
     ) {
    DAT_004d59a4 = 0;
    return CONCAT44(local_4,local_4);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

