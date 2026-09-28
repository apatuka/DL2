// LoadCursorA @ 004b4131 size=6 sig=HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName) cc=__stdcall
// callers: CYGame_CreateWindow,RegisterWindowClasses,FUN_0048b1c0
// callees: 

HCURSOR LoadCursorA(HINSTANCE hInstance,LPCSTR lpCursorName)

{
  HCURSOR pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4131. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadCursorA(hInstance,lpCursorName);
  return pHVar1;
}

