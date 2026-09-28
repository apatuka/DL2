// FUN_0049624e @ 0049624e size=54 sig=undefined FUN_0049624e() cc=unknown
// callers: FUN_00496284
// callees: FUN_00489c98

bool FUN_0049624e(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if (DAT_0051e090 == 0) {
    iVar1 = FUN_00489c98(param_1,param_2);
    if (iVar1 != 0) {
      DAT_0051e090 = 3;
    }
  }
  return DAT_0051e090 != 0;
}

