// TlsSetValue @ 004b3fff size=6 sig=BOOL TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue) cc=__stdcall
// callers: FUN_004b366c
// callees: 

BOOL TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3fff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TlsSetValue(dwTlsIndex,lpTlsValue);
  return BVar1;
}

