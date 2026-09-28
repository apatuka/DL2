// FUN_0048d2e7 @ 0048d2e7 size=69 sig=undefined FUN_0048d2e7() cc=unknown
// callers: FUN_004643cc,FUN_004878a8,FUN_0048149c,FUN_004a26e8,FUN_00440b68,FUN_004812f4,FUN_0046458c,FUN_00468a28,FUN_00449dec,FUN_004644f8,FUN_00464620,DisableMainInterface_c1a4,FUN_00415180,FUN_0047fffc,FUN_004877c8,FUN_00464354,FUN_00480b80,BlitSprite8,FUN_0046411c,FUN_00458d80,DisableMainInterface,FUN_00487e34,FUN_0043acd4,FUN_004897ea,FUN_00459864
// callees: FUN_0048e656,FUN_0048d29b,FUN_0048c434
// strings: \"..\\\\src\\\\win\\\\offport.c\"

void FUN_0048d2e7(undefined4 param_1)

{
  FUN_0048d29b();
  DAT_0065e7a4 = (undefined4 *)((int)DAT_0065e7a4 + -4);
  if (DAT_0065e7a4 < DAT_0051bde4) {
    FUN_0048e656(0x577,s____src_win_offport_c_0051c2c9);
  }
  *DAT_0065e7a4 = DAT_0051bddc;
  FUN_0048c434(param_1);
  return;
}

