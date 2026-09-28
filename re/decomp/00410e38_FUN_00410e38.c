// FUN_00410e38 @ 00410e38 size=57 sig=undefined FUN_00410e38() cc=unknown
// callers: FUN_004111ec
// callees: FUN_00410dbc

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410e38(int param_1,int param_2)

{
  _DAT_005331e4 = _DAT_005331e4 + 1;
  FUN_00410dbc(1,1);
  FUN_00410dbc(param_2,DAT_005331d4);
  if (param_2 != 0) {
    FUN_00410dbc(param_1 + -3,4);
  }
  return;
}

