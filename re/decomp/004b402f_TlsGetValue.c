// TlsGetValue @ 004b402f size=6 sig=LPVOID TlsGetValue(DWORD dwTlsIndex) cc=__stdcall
// callers: FUN_004b366c
// callees: 

LPVOID TlsGetValue(DWORD dwTlsIndex)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b402f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = TlsGetValue(dwTlsIndex);
  return pvVar1;
}

