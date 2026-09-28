// LoadIconA @ 004b412b size=6 sig=HICON LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName) cc=__stdcall
// callers: CYGame_CreateWindow,RegisterWindowClasses
// callees: 

HICON LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName)

{
  HICON pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b412b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadIconA(hInstance,lpIconName);
  return pHVar1;
}

