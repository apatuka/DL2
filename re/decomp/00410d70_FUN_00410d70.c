// FUN_00410d70 @ 00410d70 size=76 sig=undefined FUN_00410d70() cc=unknown
// callers: FUN_00410dbc
// callees: 

void FUN_00410d70(int param_1)

{
  DAT_0053319c = DAT_0053319c >> 1;
  if (param_1 != 0) {
    DAT_0053319c = DAT_0053319c | 0x80;
  }
  DAT_00533198 = DAT_00533198 + 1;
  if (DAT_00533198 == 8) {
    DAT_00533198 = 0;
    *(byte *)(DAT_005331c8 + DAT_005331cc) = DAT_0053319c;
    DAT_005331cc = DAT_005331cc + 1;
  }
  return;
}

