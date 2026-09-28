// FUN_004b10c0 @ 004b10c0 size=108 sig=undefined FUN_004b10c0() cc=unknown
// callers: FUN_004b0654
// callees: VirtualAlloc

undefined4 FUN_004b10c0(int param_1,undefined4 *param_2,uint *param_3)

{
  LPVOID pvVar1;
  uint dwSize;
  
  if (DAT_00521228 == 0) {
    if ((DAT_0069f79c == 2) || (DAT_0069f79c == 1)) {
      DAT_00521228 = 0x100000;
    }
    else {
      DAT_00521228 = 0x400000;
    }
  }
  dwSize = (param_1 + DAT_00521228) - 1U & ~(DAT_00521228 - 1U);
  pvVar1 = VirtualAlloc((LPVOID)0x0,dwSize,0x2000,1);
  *param_2 = pvVar1;
  if (pvVar1 == (LPVOID)0x0) {
    return 0;
  }
  *param_3 = dwSize;
  return 1;
}

