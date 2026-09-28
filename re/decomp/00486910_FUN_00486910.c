// FUN_00486910 @ 00486910 size=84 sig=undefined FUN_00486910() cc=unknown
// callers: ResetVariables,WinMain
// callees: memset

void FUN_00486910(int param_1)

{
  DAT_0065e3ac = 0;
  DAT_0065e424 = DAT_004d5af0;
  memset(&DAT_0065e43a,0,0xe);
  if (param_1 != 0) {
    memset(&DAT_0065e42c,0,0xe);
    memset(&DAT_0065e404,0,0x1c);
  }
  return;
}

