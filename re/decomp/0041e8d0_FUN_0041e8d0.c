// FUN_0041e8d0 @ 0041e8d0 size=40 sig=undefined FUN_0041e8d0() cc=unknown
// callers: FUN_004694c0,FUN_00469b2c,FUN_00469744,FUN_0046a020,FUN_004634a0
// callees: FUN_0041e674,FUN_0041e680

int FUN_0041e8d0(int param_1)

{
  int iVar1;
  
  DAT_0053b880 = param_1;
  iVar1 = param_1 / 5;
  if (param_1 % 5 == 0) {
    FUN_0041e680();
    iVar1 = FUN_0041e674();
  }
  return iVar1;
}

