// FUN_00481098 @ 00481098 size=49 sig=undefined FUN_00481098() cc=unknown
// callers: FUN_0043a914,FUN_0043a984,FUN_0043aa04
// callees: FUN_00449dec,FUN_00480d78

void FUN_00481098(void)

{
  if (DAT_004d59b4 == 1) {
    DAT_004dccbc = DAT_004dccbc ^ 1;
    FUN_00480d78();
    FUN_00449dec();
    return;
  }
  if (DAT_004d59b4 == 2) {
    DAT_004dccbc = DAT_004dccbc ^ 1;
    FUN_00449dec();
  }
  return;
}

