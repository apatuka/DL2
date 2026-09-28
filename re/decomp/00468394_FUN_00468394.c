// FUN_00468394 @ 00468394 size=219 sig=undefined FUN_00468394() cc=unknown
// callers: 
// callees: FUN_00430abc,FUN_00471170
// strings: \".\\\\deadlock.ini\"

undefined4 FUN_00468394(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_ac [12];
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined1 local_90;
  undefined4 local_8e;
  undefined4 local_8a;
  undefined4 local_86;
  undefined4 local_62;
  undefined4 local_5a;
  undefined4 local_56;
  undefined4 local_52;
  undefined4 local_4e;
  undefined4 local_38;
  undefined4 local_4;
  
  if (DAT_004d59a8 == '\0') {
    iVar1 = FUN_00430abc();
  }
  else {
    FUN_00471170(s___deadlock_ini_004d5277,auStack_ac);
    DAT_004d5aec = local_a0;
    DAT_004d5b00 = local_90;
    DAT_004d5af0 = local_9c;
    DAT_004d5af8 = local_98;
    DAT_004d5afc = local_94;
    DAT_004d5b0c = local_86;
    DAT_004d5b04 = local_8a;
    DAT_004d5af4 = local_4;
    DAT_004d5b08 = local_8e;
    DAT_004d5a90 = local_38;
    DAT_004d5b34 = local_56;
    DAT_004d5b38 = local_52;
    DAT_004d5b2c = local_62;
    DAT_004d5b30 = local_5a;
    DAT_004d5b3c = local_4e;
    iVar1 = 0x2c;
  }
  if (iVar1 == 0x2c) {
    uVar2 = 0x3d;
  }
  else {
    uVar2 = 0x35;
  }
  return uVar2;
}

