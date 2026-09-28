// FUN_0049ef88 @ 0049ef88 size=38 sig=undefined FUN_0049ef88() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049d27f

undefined4
FUN_0049ef88(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  undefined4 uVar1;
  
  if (*(int *)(param_2 + 0x1c) == 6) {
    uVar1 = FUN_0049d27f(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

