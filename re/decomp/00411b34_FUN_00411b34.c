// FUN_00411b34 @ 00411b34 size=32 sig=undefined FUN_00411b34() cc=unknown
// callers: OpenDataFiles
// callees: FUN_004116f4

undefined4 * FUN_00411b34(undefined4 *param_1,undefined4 param_2)

{
  FUN_004116f4(param_1);
  *param_1 = &PTR_FUN_004b6fc4;
  param_1[6] = param_2;
  return param_1;
}

