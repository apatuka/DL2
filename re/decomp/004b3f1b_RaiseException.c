// RaiseException @ 004b3f1b size=6 sig=void RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, ULONG_PTR * lpArguments) cc=__stdcall
// callers: FUN_004a78a4
// callees: 

void RaiseException(DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,
                   ULONG_PTR *lpArguments)

{
                    /* WARNING: Could not recover jumptable at 0x004b3f1b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RaiseException(dwExceptionCode,dwExceptionFlags,nNumberOfArguments,lpArguments);
  return;
}

