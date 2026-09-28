// FUN_00446b3c @ 00446b3c size=88 sig=undefined FUN_00446b3c() cc=unknown
// callers: FUN_00401a18,FUN_0040f794,FUN_0040e470,FUN_00401ac0,FUN_00442c44,FUN_004422bc,RaceInit,FUN_00401320,FUN_00442978,FUN_004853f4,FUN_00446fd4,FUN_0046c254
// callees: FUN_00446440,FUN_00446b08,FUN_0045dfb0

void FUN_00446b3c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  FUN_0045dfb0(param_5);
  FUN_00446b08(1000,param_4);
  DAT_00564214 = param_1;
  DAT_004c528c = 0;
  DAT_004c5290 = 10000;
  if (param_2 != 0) {
    FUN_00446440(param_1,0,param_2,param_3,param_4,param_5);
  }
  return;
}

