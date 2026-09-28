// FUN_0049f28c @ 0049f28c size=48 sig=undefined FUN_0049f28c() cc=unknown
// callers: FUN_0049f4c2
// callees: FUN_0049f09b,FUN_0049bb73

undefined4 FUN_0049f28c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (*(int *)(param_2 + 0x1c) == 9) {
    uVar1 = FUN_0049bb73(param_1,param_2,param_3,param_4);
  }
  else {
    FUN_0049f09b(param_2,param_4);
    uVar1 = 1;
  }
  return uVar1;
}

