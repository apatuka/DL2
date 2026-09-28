// LoadResource @ 004b3ea3 size=6 sig=HGLOBAL LoadResource(HMODULE hModule, HRSRC hResInfo) cc=__stdcall
// callers: FUN_00465640
// callees: 

HGLOBAL LoadResource(HMODULE hModule,HRSRC hResInfo)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ea3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LoadResource(hModule,hResInfo);
  return pvVar1;
}

