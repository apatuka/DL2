// FUN_00496b2c @ 00496b2c size=56 sig=undefined FUN_00496b2c() cc=unknown
// callers: 
// callees: FUN_00496a97

bool FUN_00496b2c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                 undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = FUN_00496a97(param_1,param_2,param_3);
  if (iVar1 != 0) {
    *param_5 = *(undefined4 *)(iVar1 + param_4 * 8);
    param_5[1] = *(undefined4 *)(iVar1 + 4 + param_4 * 8);
  }
  return iVar1 != 0;
}

