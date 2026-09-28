// FUN_004b366c @ 004b366c size=41 sig=undefined FUN_004b366c() cc=unknown
// callers: FUN_004b26cc,FUN_004b2520,FUN_004ae5b0,FUN_004b3e08,FUN_004ae5d8,FUN_004ae594,FUN_004acce4,FUN_004b2780,FUN_004b12c4
// callees: FUN_004b3698,TlsGetValue,TlsSetValue

LPVOID FUN_004b366c(void)

{
  LPVOID lpTlsValue;
  
  lpTlsValue = TlsGetValue(DAT_0069f888);
  if (lpTlsValue == (LPVOID)0x0) {
    lpTlsValue = (LPVOID)FUN_004b3698();
    TlsSetValue(DAT_0069f888,lpTlsValue);
  }
  return lpTlsValue;
}

