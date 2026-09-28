// lstrcatA @ 004b3e8b size=6 sig=LPSTR lstrcatA(LPSTR lpString1, LPCSTR lpString2) cc=__stdcall
// callers: FUN_00437a3c,FUN_00417434,FUN_00431734
// callees: 

LPSTR lstrcatA(LPSTR lpString1,LPCSTR lpString2)

{
  LPSTR pCVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar1 = lstrcatA(lpString1,lpString2);
  return pCVar1;
}

