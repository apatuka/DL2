// FUN_00461d80 @ 00461d80 size=282 sig=undefined FUN_00461d80() cc=unknown
// callers: 
// callees: CreateFileA,ReadFile,wsprintfA,FUN_0042836c,SetFilePointer,CloseHandle
// strings: \"Could not open file %s.\"|\"Load Game Error\"

int FUN_00461d80(LPCSTR param_1)

{
  HANDLE hFile;
  DWORD DVar1;
  BOOL BVar2;
  undefined1 local_4a0 [2];
  char local_49e;
  undefined1 local_1c8 [20];
  undefined1 local_1b4 [62];
  int local_176;
  CHAR local_108 [256];
  DWORD local_8;
  
  hFile = CreateFileA(param_1,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000000,(HANDLE)0x0);
  if ((hFile == (HANDLE)0xffffffff) ||
     (DVar1 = SetFilePointer(hFile,0x9c,(PLONG)0x0,0), DVar1 == 0xffffffff)) {
    wsprintfA(local_108,PTR_s_Could_not_open_file__s__00509a04,param_1);
    FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_108,4,0,0);
    if (hFile != (HANDLE)0x0) {
      CloseHandle(hFile);
    }
    return -1;
  }
  BVar2 = ReadFile(hFile,local_1b4,0xac,&local_8,(LPOVERLAPPED)0x0);
  if ((BVar2 != 0) &&
     (((BVar2 = ReadFile(hFile,local_1c8,0x14,&local_8,(LPOVERLAPPED)0x0), BVar2 != 0 &&
       (DVar1 = SetFilePointer(hFile,local_176 * 0x2d8,(PLONG)0x0,1), DVar1 != 0xffffffff)) &&
      (BVar2 = ReadFile(hFile,local_4a0,0x2d8,&local_8,(LPOVERLAPPED)0x0), BVar2 == 0)))) {
    CloseHandle(hFile);
    return (int)local_49e;
  }
  CloseHandle(hFile);
  return -1;
}

