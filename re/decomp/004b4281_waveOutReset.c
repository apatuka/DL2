// waveOutReset @ 004b4281 size=6 sig=MMRESULT waveOutReset(HWAVEOUT hwo) cc=__stdcall
// callers: FUN_00412f10,FUN_00412e94,WaveOut_Init
// callees: 

MMRESULT waveOutReset(HWAVEOUT hwo)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4281. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutReset(hwo);
  return MVar1;
}

