// FUN_0048dd95 @ 0048dd95 size=35 sig=undefined FUN_0048dd95() cc=unknown
// callers: InitCYGame,FUN_00493564
// callees: FUN_00495162,GetTickCount
// strings: \"Clock started\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048dd95(void)

{
  _DAT_0065e994 = GetTickCount();
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Clock_started_0051c30c);
  }
  return;
}

