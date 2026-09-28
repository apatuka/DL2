// timeGetDevCaps @ 004b427b size=6 sig=MMRESULT timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc) cc=__stdcall
// callers: Timer_Init
// callees: 

MMRESULT timeGetDevCaps(LPTIMECAPS ptc,UINT cbtc)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b427b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = timeGetDevCaps(ptc,cbtc);
  return MVar1;
}

