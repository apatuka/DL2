// GetStdHandle @ 004b4059 size=6 sig=HANDLE GetStdHandle(DWORD nStdHandle) cc=__stdcall
// callers: FUN_004b1570,FUN_004acb90
// callees: 

HANDLE GetStdHandle(DWORD nStdHandle)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4059. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetStdHandle(nStdHandle);
  return pvVar1;
}

