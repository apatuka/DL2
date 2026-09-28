// FUN_0049f947 @ 0049f947 size=49 sig=undefined FUN_0049f947() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049f8a1,FUN_0049f8dd

void FUN_0049f947(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x1c) == 2) {
      uVar2 = *(undefined4 *)(param_1 + 0x20);
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049f8dd(uVar1,uVar2,param_1);
    }
    else {
      FUN_0049f8a1(param_1,param_2);
    }
  }
  return;
}

