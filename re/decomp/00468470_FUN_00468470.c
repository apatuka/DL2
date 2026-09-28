// FUN_00468470 @ 00468470 size=95 sig=undefined FUN_00468470() cc=unknown
// callers: 
// callees: FUN_00471068,FUN_00427e30
// strings: \"Game 1\"|\".\\\\deadlock.ini\"

undefined4 FUN_00468470(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_9c [156];
  
  if (DAT_004d59a8 == '\0') {
    iVar1 = FUN_00427e30();
  }
  else {
    FUN_00471068(s___deadlock_ini_004d5277,local_9c,s_Game_1_005097c4,0x40);
    iVar1 = 5;
  }
  if (iVar1 == 5) {
    if (DAT_0058ed2e == '\0') {
      uVar2 = 0x3c;
    }
    else {
      uVar2 = 0x40;
    }
  }
  else {
    uVar2 = 0x37;
  }
  return uVar2;
}

