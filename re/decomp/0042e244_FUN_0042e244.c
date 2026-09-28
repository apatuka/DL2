// FUN_0042e244 @ 0042e244 size=113 sig=undefined FUN_0042e244() cc=unknown
// callers: FUN_00477660,FUN_00477620
// callees: DebugMessage,MessagePump,FUN_0042da3c
// strings: \"Early Select Race\"

void FUN_0042e244(int param_1,undefined4 param_2)

{
  if ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03') {
    (&DAT_0059f162)[param_1 * 0x2d8] = (char)param_2;
    while (DAT_004d59b4 != 0x48) {
      MessagePump();
    }
    FUN_0042da3c();
  }
  else {
    (&DAT_00557c84)[DAT_004c3674 * 2] = param_1;
    *(undefined4 *)(&DAT_00557c88 + DAT_004c3674 * 8) = param_2;
    DAT_004c3674 = DAT_004c3674 + 1;
    DebugMessage(s_Early_Select_Race_004c3699);
  }
  return;
}

