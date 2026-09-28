// GetExitCodeProcess @ 004b4089 size=6 sig=BOOL GetExitCodeProcess(HANDLE hProcess, LPDWORD lpExitCode) cc=__stdcall
// callers: FUN_004b1fb4
// callees: 

BOOL GetExitCodeProcess(HANDLE hProcess,LPDWORD lpExitCode)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4089. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetExitCodeProcess(hProcess,lpExitCode);
  return BVar1;
}

