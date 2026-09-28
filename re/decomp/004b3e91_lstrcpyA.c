// lstrcpyA @ 004b3e91 size=6 sig=LPSTR lstrcpyA(LPSTR lpString1, LPCSTR lpString2) cc=__stdcall
// callers: FUN_00437a3c,FUN_00431734
// callees: 

LPSTR lstrcpyA(LPSTR lpString1,LPCSTR lpString2)

{
  LPSTR pCVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e91. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pCVar1 = lstrcpyA(lpString1,lpString2);
  return pCVar1;
}

