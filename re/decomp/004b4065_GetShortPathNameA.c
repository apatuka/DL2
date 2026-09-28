// GetShortPathNameA @ 004b4065 size=6 sig=DWORD GetShortPathNameA(LPCSTR lpszLongPath, LPSTR lpszShortPath, DWORD cchBuffer) cc=__stdcall
// callers: FUN_004b1e64
// callees: 

DWORD GetShortPathNameA(LPCSTR lpszLongPath,LPSTR lpszShortPath,DWORD cchBuffer)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4065. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetShortPathNameA(lpszLongPath,lpszShortPath,cchBuffer);
  return DVar1;
}

