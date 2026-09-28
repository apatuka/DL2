// FUN_004addb4 @ 004addb4 size=41 sig=undefined FUN_004addb4() cc=unknown
// callers: FUN_004a6b00,FUN_00489159,FUN_004add90,FUN_0049cd32,FUN_004a6b98
// callees: 

uint FUN_004addb4(uint param_1)

{
  if (param_1 == 0xffffffff) {
    return 0xffffffff;
  }
  param_1 = param_1 & 0xff;
  if (((&DAT_005209ce)[param_1 * 2] & 2) != 0) {
    return param_1 - 0x20;
  }
  return param_1;
}

