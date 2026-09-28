// LoadLibraryA @ 004b4023 size=6 sig=HMODULE LoadLibraryA(LPCSTR lpLibFileName) cc=__stdcall
// callers: FUN_0046cc14,LoadSmacker
// callees: 

HMODULE LoadLibraryA(LPCSTR lpLibFileName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4023. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadLibraryA(lpLibFileName);
  return pHVar1;
}

