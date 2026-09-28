// SynchronizeGame @ 0047b3a8 size=257 sig=undefined SynchronizeGame() cc=unknown
// callers: WinMain
// callees: FUN_00427ee8,FUN_0049117e,CalculateGameCRC,FUN_00427eb4,memcpy,FUN_00474cc4,FUN_00474d0c
// strings: \"SyncGame\"

/* Sends/receives the full game state for resync */

undefined4 SynchronizeGame(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_78 [28];
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_54;
  undefined4 local_4e;
  undefined2 local_46;
  undefined2 local_44;
  undefined1 local_42 [66];
  
  if (((DAT_0058f1f4 != DAT_004d5a58) && (DAT_0058f1fc != 0)) && (DAT_004d59bc != 0)) {
    iVar1 = CalculateGameCRC(local_78);
    if (iVar1 != 0) {
      local_46 = (undefined2)DAT_0058f1f4;
      local_44 = (undefined2)DAT_0059f154;
      local_5b = (&DAT_0059f164)[DAT_0058f1f4 * 0x2d8];
      local_5a = 0xff;
      local_5c = DAT_004d5a54;
      local_4e = 0x5c;
      local_54 = 0x44;
      memcpy(local_42,local_78,0x1c);
      FUN_00474cc4(s_SyncGame_004dc3e6,&local_5c,0);
      iVar1 = FUN_00474d0c(0x44);
      if (iVar1 == 1) {
        uVar5 = 2;
        uVar4 = 0;
        uVar2 = FUN_0049117e(0,0x54415453,0x11);
        uVar3 = FUN_0049117e(0,0x54415453,0x10);
        FUN_00427eb4(0,uVar3,uVar2,uVar4,uVar5);
        FUN_00474d0c(0x44);
        FUN_00427ee8();
      }
    }
  }
  return 1;
}

