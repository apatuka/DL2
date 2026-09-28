// GetCurrentThreadId @ 004b3ed3 size=6 sig=DWORD GetCurrentThreadId(void) cc=__stdcall
// callers: FUN_004b1528
// callees: 

DWORD GetCurrentThreadId(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ed3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentThreadId();
  return DVar1;
}

