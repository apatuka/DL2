// ReleaseMutex @ 004b3ff3 size=6 sig=BOOL ReleaseMutex(HANDLE hMutex) cc=__stdcall
// callers: FUN_0048a489,FUN_0048a667,FUN_0048a0fc,FUN_00489ef5,FUN_0048a4d2,FUN_0048a766,FUN_0048a53c,FUN_0048a06a,FUN_0048a3ef,FUN_0048a6fa,FUN_0048a440,FUN_0048a145,FUN_0048a021,FUN_0048a0b3,FUN_0048a333,FUN_0048a61d
// callees: 

BOOL ReleaseMutex(HANDLE hMutex)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ff3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ReleaseMutex(hMutex);
  return BVar1;
}

