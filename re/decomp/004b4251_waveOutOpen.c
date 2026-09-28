// waveOutOpen @ 004b4251 size=6 sig=MMRESULT waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID, LPCWAVEFORMATEX pwfx, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen) cc=__stdcall
// callers: WaveOut_Init
// callees: 

MMRESULT waveOutOpen(LPHWAVEOUT phwo,UINT uDeviceID,LPCWAVEFORMATEX pwfx,DWORD_PTR dwCallback,
                    DWORD_PTR dwInstance,DWORD fdwOpen)

{
  MMRESULT MVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4251. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  MVar1 = waveOutOpen(phwo,uDeviceID,pwfx,dwCallback,dwInstance,fdwOpen);
  return MVar1;
}

