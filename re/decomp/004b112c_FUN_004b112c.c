// FUN_004b112c @ 004b112c size=82 sig=undefined FUN_004b112c() cc=unknown
// callers: FUN_004b0654
// callees: FUN_004b1180,VirtualAlloc

undefined4 FUN_004b112c(LPVOID param_1,int param_2)

{
  LPVOID pvVar1;
  LPVOID lpAddress;
  
  lpAddress = param_1;
  while( true ) {
    if (param_2 == 0) {
      return 1;
    }
    pvVar1 = VirtualAlloc(lpAddress,0x1000,0x1000,4);
    if (pvVar1 == (LPVOID)0x0) break;
    lpAddress = (LPVOID)((int)lpAddress + 0x1000);
    param_2 = param_2 + -0x1000;
  }
  FUN_004b1180(param_1,(int)lpAddress - (int)param_1);
  return 0;
}

