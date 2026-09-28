// CheckArmy @ 00419a14 size=457 sig=undefined CheckArmy() cc=unknown
// callers: FUN_0044930c
// callees: FUN_00417d44,FUN_00418cf4,FUN_004196e4,FUN_0041991c,FUN_00426594,FUN_00419924,FUN_00417d54,FUN_004a2cb5,FUN_00417ab0,DebugMessage,FUN_00417b60,FUN_00417c00
// strings: \"gpArmy NULL in CheckArmy()\"

/* auto-named from string evidence: CheckArmy */

longlong CheckArmy(void)

{
  int iVar1;
  uint local_8;
  
  if (DAT_004b76b0 == 0) {
    DebugMessage(s_gpArmy_NULL_in_CheckArmy___004b76d4);
    return (ulonglong)local_8 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  iVar1 = FUN_004a2cb5(DAT_004b76b0,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b76b0 + 100) == 0)) {
    if (local_8 == 2) {
      FUN_00426594(&DAT_004d4c68);
    }
    else if (local_8 == 3) {
      if (DAT_005332b0 != '\0') {
        FUN_00417ab0();
        FUN_00417b60();
        FUN_00417c00();
        FUN_00417d54();
        FUN_004196e4();
      }
      FUN_0041991c();
      DAT_004d59a4 = 0;
    }
    else if (local_8 == 4) {
      FUN_00419924();
      DAT_004d59a4 = 0;
    }
  }
  else if (((DAT_005332b0 != '\0') && (iVar1 = FUN_004a2cb5(DAT_004b76b4,&local_8), iVar1 == 0)) &&
          ((local_8 != 0 && (*(int *)(DAT_004b76b4 + 100) == 0)))) {
    switch(local_8) {
    case 3:
      FUN_00417ab0();
      FUN_00417b60();
      FUN_00417c00();
      FUN_00417d54();
      FUN_004196e4();
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 4:
      FUN_004196e4();
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 8:
      FUN_00417d44(0);
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 9:
      FUN_00417d44(0x19);
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 10:
      FUN_00417d44(0x32);
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 0xb:
      FUN_00417d44(0x4b);
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    case 0xc:
      FUN_00417d44(100);
      DAT_004d59a4 = 0;
      return CONCAT44(local_8,local_8);
    }
  }
  FUN_00418cf4();
  DAT_004d59a4 = 0;
  return CONCAT44(local_8,iVar1);
}

