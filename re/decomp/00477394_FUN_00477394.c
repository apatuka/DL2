// FUN_00477394 @ 00477394 size=79 sig=undefined FUN_00477394() cc=unknown
// callers: WaitSync,ChCht,FUN_004618e8
// callees: FUN_004ae594,FUN_004779c0,FUN_0046ca60

void FUN_00477394(uint param_1)

{
  if (DAT_0058f1fc == 0) {
    FUN_004ae594(param_1);
    FUN_0046ca60(param_1);
  }
  else {
    FUN_004779c0(DAT_0058f1f4,0x4b,0,param_1 & 0xffff,(int)param_1 >> 0x10 & 0xffff,0,0);
  }
  return;
}

