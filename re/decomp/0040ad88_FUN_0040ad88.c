// FUN_0040ad88 @ 0040ad88 size=107 sig=undefined FUN_0040ad88() cc=unknown
// callers: FUN_0040be04
// callees: FUN_0040beb4

int FUN_0040ad88(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 100000;
  iVar3 = -1;
  iVar1 = 1;
  do {
    if (*(short *)(&DAT_00522592 + param_1 * 0x2648 + iVar1 * 0xc4) < iVar2) {
      iVar2 = (int)*(short *)(&DAT_00522592 + param_1 * 0x2648 + iVar1 * 0xc4);
      iVar3 = iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x32);
  if (iVar3 != -1) {
    FUN_0040beb4(&DAT_00522584 + param_1 * 0x2648 + iVar3 * 0xc4);
  }
  return iVar3;
}

