// ReadFile @ 004b404d size=6 sig=BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) cc=__stdcall
// callers: CalculateGameCRC,LoadPrefs,FUN_004612d4,FUN_00462100,FUN_004acd70,FUN_004606f4,FUN_00462328,FUN_00460a74,FUN_00461d80,FUN_00461078,FUN_0045fd28,FUN_0045ff94,FUN_00461ff4,FUN_00483120,FUN_00488ba3,FUN_004600d0,FUN_004609e8,FUN_00461418,FUN_00488f9f,FUN_00460e54,FUN_00461e9c,FUN_0045fae4,FUN_0045fecc,FUN_00483098,FUN_00461328,FUN_004601f0,FUN_00460330
// callees: 

BOOL ReadFile(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,
             LPOVERLAPPED lpOverlapped)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b404d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
  return BVar1;
}

