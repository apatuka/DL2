// GetLastError @ 004b3e61 size=6 sig=DWORD GetLastError(void) cc=__stdcall
// callers: FUN_004888d0,FUN_004acfa4,FUN_004ada84,FUN_004adbec,FUN_00498b72,CreateGamePalette2,FUN_004b1fb4,FUN_004418ec,FUN_00498b4c,FUN_004acd5c
// callees: 

DWORD GetLastError(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e61. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetLastError();
  return DVar1;
}

