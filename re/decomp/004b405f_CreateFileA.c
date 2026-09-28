// CreateFileA @ 004b405f size=6 sig=HANDLE CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) cc=__stdcall
// callers: FUN_004888ec,FUN_00488998,FUN_00483224,LoadPhaseSpriteFile,CalculateGameCRC,LoadPrefs,ChCht,FUN_00488f9f,FUN_00461e9c,FUN_00461c68,SavePrefs,FUN_004618e8,FUN_004acfa4,FUN_00461d80,LoadGlobalSprites
// callees: 

HANDLE CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
                  LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,
                  DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b405f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
                       dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
  return pvVar1;
}

