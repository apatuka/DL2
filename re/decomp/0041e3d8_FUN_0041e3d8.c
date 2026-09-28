// FUN_0041e3d8 @ 0041e3d8 size=104 sig=undefined FUN_0041e3d8() cc=unknown
// callers: FUN_0044aa00,FUN_0044ab40
// callees: FUN_0041e26c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041e3d8(undefined4 param_1,undefined4 param_2)

{
  int in_stack_00000018;
  
  DAT_0053b878 = 0;
  if (in_stack_00000018 - 2U < 5) {
    if ((0x100 << ((char)in_stack_00000018 - 2U & 0x1f) & (int)*(short *)(DAT_0053b850 + 2)) != 0) {
      DAT_0053b878 = 0;
      return 0;
    }
  }
  else if (in_stack_00000018 != 7) {
    if (3 < in_stack_00000018 - 8U) {
      DAT_0053b878 = 0;
      return 0;
    }
    FUN_0041e26c(param_1,param_2);
    DAT_0053b868 = _DAT_0053b340 + 1;
    return 1;
  }
  DAT_0053b878 = 0;
  DAT_0053b868 = in_stack_00000018;
  return 1;
}

