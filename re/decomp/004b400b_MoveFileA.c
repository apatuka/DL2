// MoveFileA @ 004b400b size=6 sig=BOOL MoveFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName) cc=__stdcall
// callers: FUN_00488d30,ChCht
// callees: 

BOOL MoveFileA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b400b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MoveFileA(lpExistingFileName,lpNewFileName);
  return BVar1;
}

