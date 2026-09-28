// waveOutUnprepareHeader @ 004b4239 size=6 sig=MMRESULT waveOutUnprepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh) cc=__stdcall
// callers: FUN_00412f10,FUN_00412e94
// callees: 

MMRESULT waveOutUnprepareHeader(HWAVEOUT hwo,LPWAVEHDR pwh,UINT cbwh)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4239. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutUnprepareHeader(hwo,pwh,cbwh);
  return MVar1;
}

