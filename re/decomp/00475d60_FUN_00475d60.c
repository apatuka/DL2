// FUN_00475d60 @ 00475d60 size=66 sig=undefined FUN_00475d60() cc=unknown
// callers: FUN_004064a0
// callees: FUN_0044bacc,FUN_004779c0,FUN_00474d90

void FUN_00475d60(int param_1)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044bacc(param_1);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x1c,(int)*(short *)(param_1 + 0x1a),0,0,0,0);
    FUN_00474d90(0x1c,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

