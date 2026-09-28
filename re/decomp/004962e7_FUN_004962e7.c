// FUN_004962e7 @ 004962e7 size=73 sig=undefined FUN_004962e7() cc=unknown
// callers: FUN_00482a1c
// callees: FUN_004962d6,FUN_0049604c,FUN_00495162,FUN_004989cf
// strings: \"WARNING:Objects still in sound list.\\r\\n\"

void FUN_004962e7(void)

{
  FUN_0049604c();
  if (DAT_0051e08c != (int *)0x0) {
    if (((DAT_0051dcc5 & 0x20) != 0) && (*DAT_0051e08c != 0)) {
      FUN_00495162(s_WARNING_Objects_still_in_sound_l_0051e0a5);
    }
    FUN_004989cf(DAT_0051e08c);
    DAT_0051e08c = (int *)0x0;
  }
  FUN_004962d6();
  return;
}

