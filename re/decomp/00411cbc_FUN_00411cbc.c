// FUN_00411cbc @ 00411cbc size=32 sig=undefined FUN_00411cbc() cc=unknown
// callers: FUN_00412654
// callees: FUN_004116f4

undefined4 * FUN_00411cbc(undefined4 *param_1,undefined4 param_2)

{
  FUN_004116f4(param_1);
  *param_1 = &PTR_FUN_004b6fc0;
  param_1[6] = param_2;
  return param_1;
}

