// GetDateFormatA @ 004b3f8d size=6 sig=int GetDateFormatA(LCID Locale, DWORD dwFlags, SYSTEMTIME * lpDate, LPCSTR lpFormat, LPSTR lpDateStr, int cchDate) cc=__stdcall
// callers: FUN_004ad6c8
// callees: 

int GetDateFormatA(LCID Locale,DWORD dwFlags,SYSTEMTIME *lpDate,LPCSTR lpFormat,LPSTR lpDateStr,
                  int cchDate)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f8d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDateFormatA(Locale,dwFlags,lpDate,lpFormat,lpDateStr,cchDate);
  return iVar1;
}

