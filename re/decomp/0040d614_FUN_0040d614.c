// FUN_0040d614 @ 0040d614 size=55 sig=undefined FUN_0040d614() cc=unknown
// callers: FUN_0040d808,FUN_0040e8f0,FUN_0040d64c
// callees: FUN_00446b94

int FUN_0040d614(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  FUN_00446b94(param_1,param_2,1000,param_4,param_3,0x2000 << ((byte)param_3 & 0x1f));
  return (int)*(short *)(param_2 + 0xa70 + param_3 * 2);
}

