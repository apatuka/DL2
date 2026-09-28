// waveOutPause @ 004b424b size=6 sig=MMRESULT waveOutPause(HWAVEOUT hwo) cc=__stdcall
// callers: WaveOut_Init
// callees: 

MMRESULT waveOutPause(HWAVEOUT hwo)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b424b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutPause(hwo);
  return MVar1;
}

