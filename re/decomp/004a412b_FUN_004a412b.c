// FUN_004a412b @ 004a412b size=43 sig=undefined FUN_004a412b() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049ea99,FUN_0049deac

undefined4 FUN_004a412b(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x1c) == 5) {
    uVar1 = FUN_0049ea99(param_1);
    param_3 = FUN_0049deac(uVar1,param_1,param_3);
  }
  return param_3;
}

