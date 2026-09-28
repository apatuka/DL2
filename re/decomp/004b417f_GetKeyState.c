// GetKeyState @ 004b417f size=6 sig=SHORT GetKeyState(int nVirtKey) cc=__stdcall
// callers: FUN_004217a0,FUN_0041e440,FUN_0048dfdf,FUN_0045be7c,FUN_0041db10,FUN_00419924,FUN_0045b448,FUN_0048dfc3,FUN_00419eac,FUN_0041e26c,FUN_0048dfa7,FUN_0048e4c1,FUN_0041a470,FUN_0048e4f1,FUN_004213fc,FUN_0045ccf8,FUN_00421178,FUN_0048d920,FUN_0041a204
// callees: 

SHORT GetKeyState(int nVirtKey)

{
  SHORT SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b417f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = GetKeyState(nVirtKey);
  return SVar1;
}

