// FUN_00495b28 @ 00495b28 size=74 sig=undefined FUN_00495b28() cc=unknown
// callers: FUN_00489c3e
// callees: FUN_004a6964

bool FUN_00495b28(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 < 4) {
    *(undefined4 *)(&DAT_0065edc0 + param_1 * 0xc) = param_2;
    (&DAT_0065edc4)[param_1 * 3] = param_3;
    FUN_004a6964(&DAT_0065edc8 + param_1 * 0xc,param_4);
  }
  return param_1 < 4;
}

