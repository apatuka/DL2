// SetEnvironmentVariableA @ 004b3fcf size=6 sig=BOOL SetEnvironmentVariableA(LPCSTR lpName, LPCSTR lpValue) cc=__stdcall
// callers: FUN_004ac688
// callees: 

BOOL SetEnvironmentVariableA(LPCSTR lpName,LPCSTR lpValue)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3fcf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetEnvironmentVariableA(lpName,lpValue);
  return BVar1;
}

