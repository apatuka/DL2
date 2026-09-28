// FUN_0049f267 @ 0049f267 size=37 sig=undefined FUN_0049f267() cc=unknown
// callers: FUN_0049f4c2
// callees: FUN_0049c45d

undefined4 FUN_0049f267(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (*(int *)(param_2 + 0x1c) == 9) {
    uVar1 = FUN_0049c45d(param_1,param_2,param_3,param_4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

