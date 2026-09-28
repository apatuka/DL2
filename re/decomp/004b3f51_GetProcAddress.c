// GetProcAddress @ 004b3f51 size=6 sig=FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName) cc=__stdcall
// callers: FUN_0046cc14
// callees: 

FARPROC GetProcAddress(HMODULE hModule,LPCSTR lpProcName)

{
  FARPROC pFVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f51. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pFVar1 = GetProcAddress(hModule,lpProcName);
  return pFVar1;
}

