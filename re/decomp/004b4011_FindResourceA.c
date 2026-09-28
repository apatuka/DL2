// FindResourceA @ 004b4011 size=6 sig=HRSRC FindResourceA(HMODULE hModule, LPCSTR lpName, LPCSTR lpType) cc=__stdcall
// callers: FUN_00465640
// callees: 

HRSRC FindResourceA(HMODULE hModule,LPCSTR lpName,LPCSTR lpType)

{
  HRSRC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4011. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindResourceA(hModule,lpName,lpType);
  return pHVar1;
}

