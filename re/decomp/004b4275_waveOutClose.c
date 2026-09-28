// waveOutClose @ 004b4275 size=6 sig=MMRESULT waveOutClose(HWAVEOUT hwo) cc=__stdcall
// callers: FUN_00412584,FUN_00412f10,FUN_00412e94,WaveOut_Init
// callees: 

MMRESULT waveOutClose(HWAVEOUT hwo)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4275. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutClose(hwo);
  return MVar1;
}

