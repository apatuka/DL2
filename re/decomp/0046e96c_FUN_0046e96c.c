// FUN_0046e96c @ 0046e96c size=20 sig=undefined FUN_0046e96c() cc=unknown
// callers: SyncBeginTurn,ResetNetGame,FUN_0046eda8,WaitSync
// callees: timeGetTime

void FUN_0046e96c(void)

{
  if (DAT_004d5a78 == 0) {
    DAT_006520a4 = timeGetTime();
  }
  return;
}

