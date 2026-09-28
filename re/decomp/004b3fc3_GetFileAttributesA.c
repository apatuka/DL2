// GetFileAttributesA @ 004b3fc3 size=6 sig=DWORD GetFileAttributesA(LPCSTR lpFileName) cc=__stdcall
// callers: FUN_004acfa4,FUN_00488b0f,FUN_004ace38
// callees: 

DWORD GetFileAttributesA(LPCSTR lpFileName)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3fc3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetFileAttributesA(lpFileName);
  return DVar1;
}

