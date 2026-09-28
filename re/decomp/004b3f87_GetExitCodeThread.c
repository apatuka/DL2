// GetExitCodeThread @ 004b3f87 size=6 sig=BOOL GetExitCodeThread(HANDLE hThread, LPDWORD lpExitCode) cc=__stdcall
// callers: FUN_00494f0f
// callees: 

BOOL GetExitCodeThread(HANDLE hThread,LPDWORD lpExitCode)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f87. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetExitCodeThread(hThread,lpExitCode);
  return BVar1;
}

