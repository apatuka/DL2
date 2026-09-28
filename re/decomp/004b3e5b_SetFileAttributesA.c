// SetFileAttributesA @ 004b3e5b size=6 sig=BOOL SetFileAttributesA(LPCSTR lpFileName, DWORD dwFileAttributes) cc=__stdcall
// callers: FUN_00488b59
// callees: 

BOOL SetFileAttributesA(LPCSTR lpFileName,DWORD dwFileAttributes)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e5b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetFileAttributesA(lpFileName,dwFileAttributes);
  return BVar1;
}

