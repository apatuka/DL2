// FUN_00427a6c @ 00427a6c size=65 sig=undefined FUN_00427a6c() cc=unknown
// callers: RaceInit
// callees: FUN_0042740c,SyncBeginTurn,FUN_004272f8,FUN_0042726c,FUN_00427440

void FUN_00427a6c(void)

{
  SyncBeginTurn(0);
  if (DAT_0058f1ec == 0) {
    DAT_004b7d70 = 1;
    FUN_004272f8();
    FUN_0042726c();
    while (DAT_00557578 == 0) {
      FUN_00427440();
    }
    FUN_0042740c();
    DAT_004b7d70 = 0;
  }
  return;
}

