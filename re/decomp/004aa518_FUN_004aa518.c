// FUN_004aa518 @ 004aa518 size=69 sig=undefined FUN_004aa518() cc=unknown
// callers: FUN_00412358,FUN_00479a88,FUN_004657e0,FUN_00412654,FUN_00479ee0,FUN_00411534,FUN_00412154,FUN_0046578c,FUN_00467e58
// callees: FUN_004aa0dc,FUN_004ab648,FUN_004ab710

uint FUN_004aa518(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  if (param_2 != 0) {
    FUN_004ab648(param_4);
    param_3 = FUN_004aa0dc(param_1,param_2 * param_3,param_4);
    param_3 = param_3 / param_2;
    FUN_004ab710(param_4);
  }
  return param_3;
}

