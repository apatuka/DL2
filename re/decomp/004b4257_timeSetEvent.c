// timeSetEvent @ 004b4257 size=6 sig=MMRESULT timeSetEvent(UINT uDelay, UINT uResolution, LPTIMECALLBACK fptc, DWORD_PTR dwUser, UINT fuEvent) cc=__stdcall
// callers: Timer_Init,FUN_00489ef5
// callees: 

MMRESULT timeSetEvent(UINT uDelay,UINT uResolution,LPTIMECALLBACK fptc,DWORD_PTR dwUser,UINT fuEvent
                     )

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4257. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = timeSetEvent(uDelay,uResolution,fptc,dwUser,fuEvent);
  return MVar1;
}

