// CreateDirectoryA @ 004b4071 size=6 sig=BOOL CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes) cc=__stdcall
// callers: FUN_00488aae
// callees: 

BOOL CreateDirectoryA(LPCSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4071. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CreateDirectoryA(lpPathName,lpSecurityAttributes);
  return BVar1;
}

