// waveOutWrite @ 004b4233 size=6 sig=MMRESULT waveOutWrite(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh) cc=__stdcall
// callers: WaveOut_Init
// callees: 

MMRESULT waveOutWrite(HWAVEOUT hwo,LPWAVEHDR pwh,UINT cbwh)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4233. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutWrite(hwo,pwh,cbwh);
  return MVar1;
}

