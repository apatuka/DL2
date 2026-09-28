// FUN_0045130c @ 0045130c size=49 sig=undefined FUN_0045130c() cc=unknown
// callers: FUN_0045209c
// callees: 

void FUN_0045130c(int param_1,int param_2,int param_3)

{
  if (param_3 == 0) {
    (&DAT_0057cf4d)[param_1 + param_2 * 0x24] = (&DAT_0057cf4d)[param_1 + param_2 * 0x24] & 0xfb;
  }
  else {
    (&DAT_0057cf4d)[param_1 + param_2 * 0x24] = (&DAT_0057cf4d)[param_1 + param_2 * 0x24] | 4;
  }
  return;
}

