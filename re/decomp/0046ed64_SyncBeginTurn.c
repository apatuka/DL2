// SyncBeginTurn @ 0046ed64 size=67 sig=undefined SyncBeginTurn() cc=unknown
// callers: RaceInit,FUN_00427a6c,WinMain
// callees: FUN_0046e9d0,FUN_0046e96c,WaitSync
// strings: \"SyncBeginTurn1\"|\"SyncBeginTurn2\"

/* Begin-of-turn synchronization (SyncBeginTurn1/2) */

void SyncBeginTurn(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  FUN_0046e96c();
  WaitSync(s_SyncBeginTurn1_004d5ca6);
  if (DAT_004d598c == 0) {
    iVar2 = 0;
    puVar1 = &DAT_0059f168;
    do {
      *puVar1 = 0;
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 0x2d8;
    } while (iVar2 < 7);
  }
  WaitSync(s_SyncBeginTurn2_004d5cb5);
  FUN_0046e9d0();
  return;
}

