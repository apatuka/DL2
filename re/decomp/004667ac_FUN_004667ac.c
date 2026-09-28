// FUN_004667ac @ 004667ac size=112 sig=undefined FUN_004667ac() cc=unknown
// callers: FUN_0047ce94,FUN_00485668
// callees: FUN_0046c9d8

undefined4 FUN_004667ac(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0046c9d8(0x24,&DAT_004d5113);
  iVar2 = iVar1;
  do {
    if ((((int)*(short *)(param_1 + 0x142 + iVar2 * 0x34) & 0xffU) ==
         *(uint *)(&DAT_004d5034 + param_2 * 4)) &&
       (*(char *)(param_1 + 0x144 + iVar2 * 0x34) == '\0')) {
      *(undefined1 *)(param_1 + 0x144 + iVar2 * 0x34) = (undefined1)param_2;
      return 1;
    }
    iVar2 = iVar2 + 1;
    if (0x23 < iVar2) {
      iVar2 = 0;
    }
  } while (iVar1 != iVar2);
  return 0;
}

