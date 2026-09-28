// FUN_00474f5c @ 00474f5c size=67 sig=undefined FUN_00474f5c() cc=unknown
// callers: FUN_00474ff0,FUN_00474fa0
// callees: FUN_0045f148,FUN_00449760,FUN_0045f000

void FUN_00474f5c(int param_1,int param_2)

{
  if (((&DAT_0059f168)[param_1 * 0x2d8] != '\0') && (param_2 == DAT_0059f154)) {
    (&DAT_0059f168)[param_1 * 0x2d8] = 0;
    FUN_0045f000();
    FUN_0045f148();
    FUN_00449760();
  }
  return;
}

