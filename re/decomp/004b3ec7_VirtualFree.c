// VirtualFree @ 004b3ec7 size=6 sig=BOOL VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) cc=__stdcall
// callers: FUN_004b1180,FUN_004b11a4
// callees: 

BOOL VirtualFree(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ec7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = VirtualFree(lpAddress,dwSize,dwFreeType);
  return BVar1;
}

