// HeapValidate @ 004b3e85 size=6 sig=BOOL HeapValidate(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) cc=__stdcall
// callers: LoadPhaseSprites
// callees: 

BOOL HeapValidate(HANDLE hHeap,DWORD dwFlags,LPCVOID lpMem)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e85. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = HeapValidate(hHeap,dwFlags,lpMem);
  return BVar1;
}

