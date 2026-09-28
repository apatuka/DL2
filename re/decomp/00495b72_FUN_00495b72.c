// FUN_00495b72 @ 00495b72 size=63 sig=undefined FUN_00495b72() cc=unknown
// callers: InitCYGame
// callees: FUN_0048f774

undefined4 FUN_00495b72(void)

{
  int iVar1;
  
  if (DAT_0051e07c == 0) {
    iVar1 = 0;
    do {
      FUN_0048f774(&DAT_0065edc0 + iVar1 * 0xc,0xc,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    DAT_0051e07c = 1;
  }
  return 1;
}

