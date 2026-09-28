// FUN_004a10b3 @ 004a10b3 size=29 sig=undefined FUN_004a10b3() cc=unknown
// callers: FUN_004a2078
// callees: FUN_004a0ff9

undefined4 FUN_004a10b3(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x20) == 1) {
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a0ff9(param_1);
  }
  return uVar1;
}

