// FUN_00421734 @ 00421734 size=107 sig=undefined FUN_00421734() cc=unknown
// callers: FUN_0044aac4,FUN_0044aa00
// callees: FUN_0041ff24,FUN_0041ff18,FUN_00421154,FUN_004213fc

undefined4 FUN_00421734(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int in_stack_00000018;
  
  DAT_0053b8c5 = 0;
  if ((in_stack_00000018 == 1) || (in_stack_00000018 - 8U < 4)) {
    FUN_004213fc(param_1,param_2);
    iVar1 = FUN_00421154(DAT_0053b8ac);
    DAT_0053b8bc = iVar1 + 0x10;
    FUN_0041ff24();
    FUN_0041ff18();
    uVar2 = 1;
  }
  else if (in_stack_00000018 - 0x10U < 0x18) {
    DAT_0053b8bc = in_stack_00000018;
    FUN_0041ff24();
    FUN_0041ff18();
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

