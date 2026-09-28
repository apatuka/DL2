// GetModuleFileNameA @ 004b4083 size=6 sig=DWORD GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize) cc=__stdcall
// callers: FUN_00488e62,FUN_0048e530,FUN_004b1570
// callees: 

DWORD GetModuleFileNameA(HMODULE hModule,LPSTR lpFilename,DWORD nSize)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4083. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetModuleFileNameA(hModule,lpFilename,nSize);
  return DVar1;
}

