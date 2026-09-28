// timeGetTime @ 004b4263 size=6 sig=DWORD timeGetTime(void) cc=__stdcall
// callers: FUN_00466fb8,FUN_0045efd0,FUN_004880e0,LoadPrefsAndInit,FUN_0048a6fa,FUN_0045f17c,FUN_0046e980,FUN_0048a82a,FUN_0045f028,FUN_0046e96c,WinMain
// callees: 

DWORD timeGetTime(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4263. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = timeGetTime();
  return DVar1;
}

