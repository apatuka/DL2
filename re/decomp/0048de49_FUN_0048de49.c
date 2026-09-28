// FUN_0048de49 @ 0048de49 size=32 sig=undefined FUN_0048de49() cc=unknown
// callers: FUN_004935d2,FUN_0046ff98
// callees: FUN_00495162
// strings: \"Keyboard input stopped\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048de49(void)

{
  _DAT_0051c300 = _DAT_0051c300 & 0xfffffffe;
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Keyboard_input_stopped_0051c344);
  }
  return;
}

