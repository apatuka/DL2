// LoadBitmapA @ 004b4215 size=6 sig=HBITMAP LoadBitmapA(HINSTANCE hInstance, LPCSTR lpBitmapName) cc=__stdcall
// callers: CreateMainWindow
// callees: 

HBITMAP LoadBitmapA(HINSTANCE hInstance,LPCSTR lpBitmapName)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4215. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadBitmapA(hInstance,lpBitmapName);
  return pHVar1;
}

