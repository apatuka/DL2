// FUN_00468800 @ 00468800 size=149 sig=undefined FUN_00468800() cc=unknown
// callers: 
// callees: FUN_004719a0,FUN_00426ba4,FUN_00458508
// strings: \".\\\\deadlock.ini\"

undefined4 FUN_00468800(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  undefined1 local_80 [64];
  undefined1 local_40 [64];
  
  if (DAT_004d59a8 != '\0') {
    FUN_004719a0(s___deadlock_ini_004d5277,0,local_88,local_84,local_80,0x40,local_80,0x20,local_40,
                 0x40);
    iVar1 = FUN_00458508(local_40);
    if (iVar1 == 0) {
      DAT_004d59a8 = 0;
      return 0x35;
    }
  }
  iVar1 = FUN_00426ba4();
  if (iVar1 == 5) {
    uVar2 = 0x41;
  }
  else if (iVar1 == 6) {
    if (DAT_004d59a8 == '\0') {
      uVar2 = 0x37;
    }
    else {
      DAT_004d59a8 = '\0';
      uVar2 = 0x35;
    }
  }
  else {
    uVar2 = 0x37;
  }
  return uVar2;
}

