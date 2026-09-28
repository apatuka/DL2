// CheckTechTree @ 0043ce4c size=280 sig=undefined CheckTechTree() cc=unknown
// callers: FUN_0044930c
// callees: DebugMessage,FUN_0043cd98,FUN_0043c988,FUN_0043cbe8,FUN_0043cc5c,FUN_0043cbf8,FUN_004a2cb5,FUN_00426594,FUN_0043cb7c
// strings: \"NULL pointers in CheckTechTree()\"

/* auto-named from string evidence: CheckTechTree */

longlong CheckTechTree(void)

{
  int iVar1;
  uint local_8;
  
  if ((DAT_004c4904 != 0) && (DAT_004c4900 != 0)) {
    DAT_004d59a4 = 1;
    DAT_0051b824 = 1;
    iVar1 = FUN_004a2cb5(DAT_004c4900,&local_8);
    if ((iVar1 == 0) && ((local_8 != 0 && (*(int *)(DAT_004c4900 + 100) == 0)))) {
      if (local_8 == 3) {
        FUN_0043cbf8();
        DAT_004d59a4 = 0;
        return (ulonglong)local_8 << 0x20;
      }
      if (local_8 == 4) {
        FUN_0043cbe8();
      }
      else if (local_8 == 5) {
        FUN_00426594(&DAT_004d4c20);
      }
      else if (local_8 == 6) {
        FUN_0043cb7c();
      }
    }
    else {
      iVar1 = FUN_004a2cb5(DAT_004c4904,&local_8);
      if ((iVar1 == 0) &&
         ((((local_8 != 0 && (*(int *)(DAT_004c4904 + 100) == 0)) && (3 < (int)local_8)) &&
          ((int)local_8 < 0xbd)))) {
        if (*(int *)(DAT_004c4904 + 0x80) == 1) {
          FUN_0043cc5c(local_8);
        }
        else if (*(int *)(DAT_004c4904 + 0x80) == 2) {
          FUN_0043cd98(local_8);
        }
      }
    }
    DAT_004d59a4 = 0;
    FUN_0043c988();
    return CONCAT44(local_8,local_8);
  }
  DebugMessage(s_NULL_pointers_in_CheckTechTree___004c492c);
  return (ulonglong)local_8 << 0x20;
}

