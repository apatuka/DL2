// FUN_00410c74 @ 00410c74 size=70 sig=undefined FUN_00410c74() cc=unknown
// callers: FUN_00410dbc,FUN_00410cbc
// callees: FUN_004ac65c

void FUN_00410c74(undefined4 param_1,int param_2)

{
  DAT_0053319c = DAT_0053319c >> 1;
  if (param_2 != 0) {
    DAT_0053319c = DAT_0053319c | 0x80;
  }
  DAT_00533198 = DAT_00533198 + 1;
  if (DAT_00533198 == 8) {
    DAT_00533198 = 0;
    FUN_004ac65c(DAT_0053319c,param_1);
  }
  return;
}

