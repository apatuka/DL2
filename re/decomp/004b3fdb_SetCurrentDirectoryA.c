// SetCurrentDirectoryA @ 004b3fdb size=6 sig=BOOL SetCurrentDirectoryA(LPCSTR lpPathName) cc=__stdcall
// callers: FUN_004ac688,FUN_00488e1b,FUN_0048e530
// callees: 

BOOL SetCurrentDirectoryA(LPCSTR lpPathName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3fdb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetCurrentDirectoryA(lpPathName);
  return BVar1;
}

