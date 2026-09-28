// FUN_004a4156 @ 004a4156 size=47 sig=undefined FUN_004a4156() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049b94f,FUN_0049dc81

undefined4 FUN_004a4156(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x1c) == 6) {
    uVar1 = FUN_0049dc81(param_1,param_2);
  }
  else if (*(int *)(param_1 + 0x1c) == 9) {
    uVar1 = FUN_0049b94f(param_1,param_2);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

