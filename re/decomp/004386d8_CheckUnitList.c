// CheckUnitList @ 004386d8 size=296 sig=undefined CheckUnitList() cc=unknown
// callers: FUN_00438aa4
// callees: FUN_00438254,DebugMessage,FUN_0048db5d,FUN_00426594,FUN_004386ac,FUN_004a2cb5,FUN_00438214
// strings: \"gpUnitList NULL in CheckUnitList()\"

/* auto-named from string evidence: CheckUnitList */

longlong CheckUnitList(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004c46b4 == 0) {
    DebugMessage(s_gpUnitList_NULL_in_CheckUnitList_004c4765);
    return (ulonglong)local_4 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  iVar1 = FUN_004a2cb5(DAT_004c46b4,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c46b4 + 100) == 0)) {
    switch(local_4) {
    case 2:
      FUN_004386ac();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 3:
      DAT_005594a8 = 1;
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 4:
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 7:
      FUN_00426594(&DAT_004d4c68);
      break;
    case 8:
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 9:
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 10:
      DAT_005594a8 = 1;
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 0xb:
      DAT_005594a8 = 1;
      FUN_00438254();
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
  }
  FUN_00438214();
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

