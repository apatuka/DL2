// GetModuleHandleA @ 004b3e43 size=6 sig=HMODULE GetModuleHandleA(LPCSTR lpModuleName) cc=__stdcall
// callers: FUN_004b298c,entry
// callees: 

HMODULE GetModuleHandleA(LPCSTR lpModuleName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e43. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetModuleHandleA(lpModuleName);
  return pHVar1;
}

