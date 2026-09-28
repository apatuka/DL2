// GetAsyncKeyState @ 004b4227 size=6 sig=SHORT GetAsyncKeyState(int vKey) cc=__stdcall
// callers: FUN_0048e00a
// callees: 

SHORT GetAsyncKeyState(int vKey)

{
  SHORT SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4227. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = GetAsyncKeyState(vKey);
  return SVar1;
}

