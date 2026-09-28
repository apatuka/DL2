// FUN_0048de1d @ 0048de1d size=44 sig=undefined FUN_0048de1d() cc=unknown
// callers: InitCYGame,FUN_00493564
// callees: FUN_00495162
// strings: \"Keyboard input inited\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048de1d(void)

{
  DAT_0065e7b0 = 0;
  DAT_0065e7ac = 0;
  _DAT_0051c300 = _DAT_0051c300 | 1;
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Keyboard_input_inited_0051c32c);
  }
  return;
}

