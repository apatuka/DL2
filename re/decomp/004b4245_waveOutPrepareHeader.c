// waveOutPrepareHeader @ 004b4245 size=6 sig=MMRESULT waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh) cc=__stdcall
// callers: WaveOut_Init
// callees: 

MMRESULT waveOutPrepareHeader(HWAVEOUT hwo,LPWAVEHDR pwh,UINT cbwh)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4245. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutPrepareHeader(hwo,pwh,cbwh);
  return MVar1;
}

