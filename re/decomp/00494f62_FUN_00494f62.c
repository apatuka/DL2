// FUN_00494f62 @ 00494f62 size=84 sig=undefined FUN_00494f62() cc=unknown
// callers: FUN_00415274
// callees: FUN_00494ebf,FUN_0048e103

undefined4 FUN_00494f62(undefined *param_1,int param_2)

{
  int iVar1;
  
  if (DAT_0051dc9c == 0) {
    FUN_0048e103();
    DAT_0051dc9c = 1;
    DAT_0065ec7c = 0;
  }
  if (param_2 != 0) {
    DAT_0065ecac = &DAT_0065e644;
    iVar1 = FUN_00494ebf();
    if (iVar1 != 0) {
      param_1 = &DAT_0065e644;
    }
  }
  DAT_0065ecac = param_1;
  return 1;
}

