// FUN_00446b94 @ 00446b94 size=89 sig=undefined FUN_00446b94() cc=unknown
// callers: FUN_00446084,FUN_0040d614,FUN_0040e1fc
// callees: FUN_00446440,FUN_00446b08,FUN_0045dfb0

void FUN_00446b94(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  FUN_0045dfb0(param_6);
  FUN_00446b08(1000,param_5);
  DAT_00564214 = param_1;
  DAT_004c528c = param_2;
  DAT_004c5290 = 10000;
  if (param_3 != 0) {
    FUN_00446440(param_1,0,param_3,param_4,param_5,param_6);
  }
  return;
}

