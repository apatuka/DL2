// FUN_004895e4 @ 004895e4 size=39 sig=undefined FUN_004895e4() cc=unknown
// callers: FUN_0048960b
// callees: 

undefined4 FUN_004895e4(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0xc) == 0x10) {
    if (*(short *)(param_1 + 0x26) == 2) {
      uVar1 = 0x80000000;
    }
    else {
      uVar1 = 0xc0000000;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

