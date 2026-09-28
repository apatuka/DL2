// FUN_0046e9d0 @ 0046e9d0 size=36 sig=undefined FUN_0046e9d0() cc=unknown
// callers: SyncBeginTurn,ResetNetGame,FUN_0046eda8,WaitSync
// callees: FUN_00414e74,FUN_00427ee8

void FUN_0046e9d0(void)

{
  if ((DAT_004d5a78 == 0) && (DAT_004d5c24 != 0)) {
    FUN_00427ee8();
    FUN_00414e74();
    DAT_004d5c24 = 0;
  }
  return;
}

