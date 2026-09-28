// FUN_00476ffc @ 00476ffc size=77 sig=undefined FUN_00476ffc() cc=unknown
// callers: FUN_0046e374,RunAITurns,FUN_0045f028,FUN_0045e554
// callees: FUN_0045f148,FUN_004779c0,FUN_00449760

void FUN_00476ffc(int param_1)

{
  if ((&DAT_0059f168)[param_1 * 0x2d8] == '\0') {
    FUN_004779c0(param_1,0x32,DAT_0059f154,0,0,0,0);
    (&DAT_0059f168)[param_1 * 0x2d8] = 1;
    FUN_0045f148();
    FUN_00449760();
  }
  return;
}

