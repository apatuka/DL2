// FUN_00426f20 @ 00426f20 size=231 sig=undefined FUN_00426f20() cc=unknown
// callers: FUN_00427440
// callees: FUN_00427854,FUN_00427278,FUN_00426eb8,FUN_0045dfb0,FUN_00426bd0

void FUN_00426f20(void)

{
  int iVar1;
  
  if (DAT_00557578 != 0) {
    FUN_0045dfb0(6);
    return;
  }
  if ((DAT_004d5aa0 == '\0') &&
     (((&DAT_0059f161)[DAT_00557788 * 0x2d8] == '\0' ||
      ('\x02' < (char)(&DAT_0059f161)[DAT_00557788 * 0x2d8])))) {
    iVar1 = FUN_00427854(DAT_00557788,1,DAT_00557784);
    if (iVar1 == -1) {
      DAT_00557784 = 1;
      iVar1 = FUN_00427854(DAT_00557788,1,1);
    }
    (&DAT_0059f166)[DAT_00557788 * 0x16c] = (short)iVar1;
    (&DAT_005a43f0)[iVar1 * 0xadc] = (undefined1)DAT_00557788;
    FUN_00426bd0(DAT_00557784);
    FUN_00426eb8();
    FUN_00427278();
  }
  return;
}

