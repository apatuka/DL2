// FUN_00499c5d @ 00499c5d size=299 sig=undefined FUN_00499c5d() cc=unknown
// callers: FUN_0049a6bb
// callees: FUN_00498ba9

undefined4 FUN_00499c5d(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_0051e214 == 0) {
    DAT_0051e214 = FUN_00498ba9(0x1200);
    if (DAT_0051e214 == 0) {
      return 0;
    }
    iVar2 = 10;
    iVar3 = 0;
    DAT_0051d6dc = DAT_0051e214;
    do {
      iVar1 = 0;
      do {
        *(char *)(DAT_0051d6dc + iVar1) = (char)((iVar1 * iVar2) / 100);
        *(char *)(DAT_0051d6dc + (0x1ff - iVar1)) = (char)((-iVar1 * iVar2) / 100);
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x100);
      DAT_0051d6dc = DAT_0051d6dc + 0x200;
      iVar2 = iVar2 + 10;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 9);
  }
  if (DAT_0051e218 == 0) {
    DAT_0051e218 = FUN_00498ba9(0x2400);
    if (DAT_0051e218 == 0) {
      return 0;
    }
    iVar2 = 10;
    iVar3 = 0;
    DAT_0051d6e0 = DAT_0051e218;
    do {
      iVar1 = 0;
      do {
        *(ushort *)(DAT_0051d6e0 + iVar1 * 2) = (ushort)((iVar1 * iVar2) / 100) & 0xff;
        *(ushort *)(DAT_0051d6e0 + (0x1ff - iVar1) * 2) = (ushort)((-iVar1 * iVar2) / 100) & 0xff;
        iVar1 = iVar1 + 1;
      } while (iVar1 < 0x100);
      DAT_0051d6e0 = DAT_0051d6e0 + 0x400;
      iVar2 = iVar2 + 10;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 9);
  }
  return 1;
}

