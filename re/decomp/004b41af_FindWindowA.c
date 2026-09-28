// FindWindowA @ 004b41af size=6 sig=HWND FindWindowA(LPCSTR lpClassName, LPCSTR lpWindowName) cc=__stdcall
// callers: WinMain
// callees: 

HWND FindWindowA(LPCSTR lpClassName,LPCSTR lpWindowName)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b41af. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindWindowA(lpClassName,lpWindowName);
  return pHVar1;
}

