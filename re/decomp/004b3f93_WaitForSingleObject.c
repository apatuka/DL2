// WaitForSingleObject @ 004b3f93 size=6 sig=DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) cc=__stdcall
// callers: FUN_0048a489,FUN_0048a667,FUN_0048a0fc,FUN_0048a4d2,FUN_0048a766,FUN_0048a53c,FUN_0048a06a,FUN_0048a3ef,FUN_0048a2a6,FUN_0048a6fa,FUN_0048a440,FUN_0048a145,FUN_0048a021,FUN_004b1fb4,FUN_0048a0b3,FUN_0048a333,FUN_0048a61d
// callees: 

DWORD WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f93. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = WaitForSingleObject(hHandle,dwMilliseconds);
  return DVar1;
}

