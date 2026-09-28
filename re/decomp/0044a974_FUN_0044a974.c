// FUN_0044a974 @ 0044a974 size=68 sig=undefined FUN_0044a974() cc=unknown
// callers: FUN_0044ac18
// callees: FUN_0045d3a4

void FUN_0044a974(undefined4 param_1,undefined4 param_2)

{
  DAT_004c5bc8 = 0;
  if ((int)DAT_004d59b4 < 8) {
    if (((DAT_004d59b4 != 7) && (1 < DAT_004d59b4)) && (DAT_004d59b4 != 5)) {
      DAT_004c5bc8 = 0;
      return;
    }
  }
  else if ((DAT_004d59b4 != 0xb) && (DAT_004d59b4 != 0x22)) {
    DAT_004c5bc8 = 0;
    return;
  }
  DAT_004c5bc8 = FUN_0045d3a4(param_1,param_2);
  return;
}

