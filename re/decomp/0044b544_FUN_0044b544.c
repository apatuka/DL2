// FUN_0044b544 @ 0044b544 size=118 sig=undefined FUN_0044b544() cc=unknown
// callers: FUN_00427440
// callees: FUN_004a5c60,DebugMessage,FUN_004a4185,GetCursorPos,FUN_0044b4f8
// strings: \"Couldn't Create Balloon Help\"

void FUN_0044b544(void)

{
  int iVar1;
  undefined4 uVar2;
  
  GetCursorPos((LPPOINT)&DAT_005644e8);
  DAT_004c5e34 = FUN_0044b4f8(&DAT_005644e8);
  if (DAT_004c5e34 != 0) {
    iVar1 = FUN_004a4185(0);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = *(undefined4 *)(iVar1 + 0x60);
    }
    DAT_004c5e2c = FUN_004a5c60(DAT_004c5e34,DAT_005644e8,DAT_005644ec,DAT_004d5c28,uVar2,1);
    if (DAT_004c5e2c != 0) {
      DAT_004c5e30 = 1;
      return;
    }
    DebugMessage(s_Couldn_t_Create_Balloon_Help_004c5e38);
  }
  return;
}

