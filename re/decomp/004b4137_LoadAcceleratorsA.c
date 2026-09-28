// LoadAcceleratorsA @ 004b4137 size=6 sig=HACCEL LoadAcceleratorsA(HINSTANCE hInstance, LPCSTR lpTableName) cc=__stdcall
// callers: CreateMainWindow
// callees: 

HACCEL LoadAcceleratorsA(HINSTANCE hInstance,LPCSTR lpTableName)

{
  HACCEL pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4137. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadAcceleratorsA(hInstance,lpTableName);
  return pHVar1;
}

