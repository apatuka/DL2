// FUN_004a57e0 @ 004a57e0 size=172 sig=undefined FUN_004a57e0() cc=unknown
// callers: InitCYGame
// callees: FUN_00490ab3,FUN_0048f774,FUN_00491b5e,FUN_00491bf7

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004a57e0(undefined4 param_1)

{
  if (DAT_0051e518 == 0) {
    DAT_0051e520 = param_1;
    DAT_0051e524 = FUN_00490ab3(0,0x544e4f46,param_1,0,0x80000000);
    if (DAT_0051e524 != 0) {
      FUN_00491bf7(DAT_0051e524);
      FUN_00491b5e(&DAT_0069f040);
    }
    DAT_0051e528 = 0;
    _DAT_0069f030 = 0;
    DAT_0069f038 = 0xffffffff;
    DAT_0069f034 = 0xffffffff;
    DAT_0069f020 = 0xffffffff;
    DAT_0069f03c = 1;
    FUN_0048f774(&DAT_0069f04c,0xa0,0);
    DAT_0051e518 = 1;
    DAT_0051e51c = 1;
  }
  return 1;
}

