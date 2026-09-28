// FUN_004b11a4 @ 004b11a4 size=33 sig=undefined FUN_004b11a4() cc=unknown
// callers: FUN_004b0654,FUN_004b092c,FUN_004b0e5c
// callees: VirtualFree

undefined4 FUN_004b11a4(LPVOID param_1)

{
  BOOL BVar1;
  
  BVar1 = VirtualFree(param_1,0,0x8000);
  if (BVar1 != 1) {
    return 0;
  }
  return 1;
}

