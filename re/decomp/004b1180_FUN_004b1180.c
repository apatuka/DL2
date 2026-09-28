// FUN_004b1180 @ 004b1180 size=35 sig=undefined FUN_004b1180() cc=unknown
// callers: FUN_004b112c,FUN_004b092c,FUN_004b0e5c
// callees: VirtualFree

undefined4 FUN_004b1180(LPVOID param_1,SIZE_T param_2)

{
  BOOL BVar1;
  
  BVar1 = VirtualFree(param_1,param_2,0x4000);
  if (BVar1 != 1) {
    return 0;
  }
  return 1;
}

