// WriteFile @ 004b4077 size=6 sig=BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) cc=__stdcall
// callers: FUN_0046002c,FUN_00460188,FUN_00461f74,FUN_0045fe58,FUN_00461308,FUN_0045ff40,FUN_004acdd4,FUN_0045fd04,FUN_00460d84,FUN_004605e0,SavePrefs,FUN_00488c1c,FUN_00460870,FUN_00460fa4,FUN_00462308,FUN_0046136c,FUN_004620dc,FUN_004b1570,FUN_004612b0,FUN_0045fa4c,FUN_00460258,FUN_004607d8
// callees: 

BOOL WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,
              LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4077. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WriteFile(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
  return BVar1;
}

