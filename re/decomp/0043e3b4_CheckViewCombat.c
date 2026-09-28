// CheckViewCombat @ 0043e3b4 size=423 sig=undefined CheckViewCombat() cc=unknown
// callers: FUN_0044930c
// callees: DebugMessage,FUN_0043e138,FUN_0043e168,FUN_0043e0b8,FUN_0043e0dc,FUN_0043e130,FUN_0043e37c,FUN_0043df3c,FUN_0043ded0,FUN_004a2cb5,FUN_0049eb44,FUN_0043e22c
// strings: \"gpViewCombat NULL in CheckViewCombat()\"

/* auto-named from string evidence: CheckViewCombat */

longlong CheckViewCombat(void)

{
  int iVar1;
  int iVar2;
  uint local_8;
  
  if (DAT_004c4950 == 0) {
    DebugMessage(s_gpViewCombat_NULL_in_CheckViewCo_004c4a30);
    return (ulonglong)local_8 << 0x20;
  }
  iVar1 = FUN_004a2cb5(DAT_004c4950,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004c4950 + 100) == 0)) {
    switch(local_8) {
    case 1:
      iVar2 = FUN_0043df3c(DAT_00559dd4);
      if (iVar2 == -1) {
        FUN_0049eb44(DAT_004c4950,1,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c4950,1,1,10,0,0);
      }
      iVar2 = FUN_0043ded0(DAT_00559dd4);
      if (iVar2 == -1) {
        FUN_0049eb44(DAT_004c4950,2,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c4950,2,1,10,0,0);
      }
      iVar2 = FUN_0043df3c(DAT_00559dd4);
      if (iVar2 != -1) {
        FUN_0043e138();
      }
      break;
    case 2:
      iVar2 = FUN_0043ded0(DAT_00559dd4);
      if (iVar2 == -1) {
        FUN_0049eb44(DAT_004c4950,2,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c4950,2,1,10,0,0);
      }
      iVar2 = FUN_0043df3c(DAT_00559dd4);
      if (iVar2 == -1) {
        FUN_0049eb44(DAT_004c4950,1,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c4950,1,1,10,0,0);
      }
      iVar2 = FUN_0043ded0(DAT_00559dd4);
      if (iVar2 != -1) {
        FUN_0043e168();
      }
      break;
    case 3:
      FUN_0043e130();
      break;
    case 4:
      FUN_0043e0b8();
      break;
    case 5:
      FUN_0043e0dc();
      break;
    case 6:
      FUN_0043e37c();
    }
  }
  FUN_0043e22c();
  return CONCAT44(local_8,iVar1);
}

