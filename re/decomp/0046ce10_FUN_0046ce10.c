// FUN_0046ce10 @ 0046ce10 size=193 sig=undefined FUN_0046ce10() cc=unknown
// callers: FUN_004618e8,ShutdownGame,WinMain
// callees: FUN_0048d13d,FUN_0043c514,FUN_00441a44,FUN_00458298,FUN_0046ee64,FUN_004419c8,FUN_00477e4c,FUN_00479a5c,FUN_004878a8,FUN_00494def,FUN_004780e4,FUN_004835bc

void FUN_0046ce10(int param_1)

{
  DAT_004d59bc = 0;
  FUN_0043c514();
  FUN_00479a5c();
  if ((param_1 != 0) && (DAT_004d8264 == 0)) {
    FUN_004780e4(DAT_0058f1f4,1);
  }
  FUN_004878a8();
  if (param_1 != 0) {
    FUN_00494def(0);
    FUN_0046ee64();
    FUN_00494def(1);
  }
  FUN_004835bc();
  FUN_00441a44();
  if (DAT_0058f1e4 != 0) {
    FUN_004419c8(DAT_0058f1e4);
    DAT_0058f1e4 = 0;
    DAT_0058f138 = 0;
    DAT_0058f134 = 0;
  }
  if (DAT_004dcc1c != 0) {
    FUN_0048d13d(DAT_004dcc1c);
    DAT_004dcc1c = 0;
  }
  if (DAT_0058f1e0 != 0) {
    FUN_004419c8(DAT_0058f1e0);
    DAT_0058f1e0 = 0;
  }
  FUN_00477e4c();
  if (param_1 != 0) {
    FUN_00458298();
  }
  return;
}

