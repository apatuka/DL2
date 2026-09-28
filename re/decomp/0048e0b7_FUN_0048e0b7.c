// FUN_0048e0b7 @ 0048e0b7 size=32 sig=undefined FUN_0048e0b7() cc=unknown
// callers: InitCYGame,FUN_00493564
// callees: FUN_00495162
// strings: \"Mouse input inited\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048e0b7(void)

{
  _DAT_0051c300 = _DAT_0051c300 | 2;
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Mouse_input_inited_0051c35d);
  }
  return;
}

