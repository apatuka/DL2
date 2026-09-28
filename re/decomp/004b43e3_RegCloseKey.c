// RegCloseKey @ 004b43e3 size=6 sig=LSTATUS RegCloseKey(HKEY hKey) cc=__stdcall
// callers: FUN_00467884
// callees: 

LSTATUS RegCloseKey(HKEY hKey)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b43e3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegCloseKey(hKey);
  return LVar1;
}

