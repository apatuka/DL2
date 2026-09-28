// GetFileSize @ 004b3f99 size=6 sig=DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh) cc=__stdcall
// callers: FUN_00488f9f,FUN_00488ce9
// callees: 

DWORD GetFileSize(HANDLE hFile,LPDWORD lpFileSizeHigh)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f99. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetFileSize(hFile,lpFileSizeHigh);
  return DVar1;
}

