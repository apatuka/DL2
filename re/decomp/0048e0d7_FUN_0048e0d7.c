// FUN_0048e0d7 @ 0048e0d7 size=32 sig=undefined FUN_0048e0d7() cc=unknown
// callers: FUN_004935d2,FUN_0046ff98
// callees: FUN_00495162
// strings: \"Mouse input stopped\\r\\n\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048e0d7(void)

{
  _DAT_0051c300 = _DAT_0051c300 & 0xfffffffd;
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Mouse_input_stopped_0051c372);
  }
  return;
}

