// FUN_0044d3f4 @ 0044d3f4 size=33 sig=undefined FUN_0044d3f4() cc=unknown
// callers: FindConstructionSite,FUN_0044d600,FUN_00402df4,FUN_0041acf8
// callees: 

undefined4 FUN_0044d3f4(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 0x13U < 0x1a) {
                    /* WARNING: Could not emulate address calculation at 0x0044d402 */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(&DAT_0044d429 +
                        CONCAT31((int3)(param_1 - 0x13U >> 8),*(undefined1 *)(param_1 + 0x44d3fc)) *
                        4))();
    return uVar1;
  }
  return 0;
}

