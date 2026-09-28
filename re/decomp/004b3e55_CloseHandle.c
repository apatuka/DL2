// CloseHandle @ 004b3e55 size=6 sig=BOOL CloseHandle(HANDLE hObject) cc=__stdcall
// callers: FUN_00483224,LoadPhaseSpriteFile,CalculateGameCRC,LoadPrefs,ChCht,FUN_00488f9f,FUN_00461e9c,FUN_004ace78,FUN_00461c68,SavePrefs,FUN_004618e8,FUN_0048a2a6,FUN_004acfa4,FUN_00461d80,FUN_004b1fb4,FUN_00494f0f,LoadGlobalSprites,FUN_00488a09
// callees: 

BOOL CloseHandle(HANDLE hObject)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e55. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CloseHandle(hObject);
  return BVar1;
}

