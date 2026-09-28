// qsort @ 004b14e8 size=42 sig=undefined qsort() cc=unknown
// callers: FUN_00412154,FUN_004233c4,FUN_0046f89c,HdxArchive_Open,FUN_0046f908
// callees: FUN_004b1304

/* RTL */

void qsort(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  DAT_0069f780 = param_3;
  if (param_3 != 0) {
    DAT_0069f77c = param_4;
    FUN_004b1304(param_1,param_2);
  }
  return;
}

