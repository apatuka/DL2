// FUN_004582e0 @ 004582e0 size=162 sig=undefined FUN_004582e0() cc=unknown
// callers: FUN_00468a28
// callees: CGNetSession_FindPlayers,CGNetService_CreateSession,CGNetSession_CreatePlayer,FUN_004a6b48
// strings: \"Deadlock 2 Host\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004582e0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_004a6b48(&DAT_0058385c,param_1,0x20);
  iVar1 = CGNetService_CreateSession(DAT_00583b74,&DAT_004d1708,&DAT_0058385c,7);
  if (iVar1 < 0) {
    uVar2 = 0;
  }
  else {
    _DAT_00583b80 = CGNetSession_FindPlayers(DAT_004d1708,&DAT_00583b7c);
    DAT_004d16f8 = 0;
    iVar1 = CGNetSession_CreatePlayer(DAT_004d1708,&DAT_004d170c,s_Deadlock_2_Host_004d172c);
    if (iVar1 < 0) {
      uVar2 = 0;
    }
    else {
      _DAT_00583b80 = CGNetSession_FindPlayers(DAT_004d1708,&DAT_00583b7c);
      _DAT_004d16fc = 0;
      DAT_00583858 = 1;
      uVar2 = 1;
    }
  }
  return uVar2;
}

