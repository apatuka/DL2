// FUN_0044a9b8 @ 0044a9b8 size=72 sig=undefined FUN_0044a9b8() cc=unknown
// callers: FUN_0044ad14
// callees: FUN_0045d478

void FUN_0044a9b8(undefined4 param_1,undefined4 param_2)

{
  if (DAT_004c5bc8 == '\0') {
    return;
  }
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
  FUN_0045d478(param_1,param_2);
  DAT_004c5bc8 = 0;
  return;
}

