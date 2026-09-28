// FUN_00461e9c @ 00461e9c size=215 sig=undefined FUN_00461e9c() cc=unknown
// callers: FUN_00468da0
// callees: CreateFileA,ReadFile,wsprintfA,FUN_0042836c,SetFilePointer,CloseHandle
// strings: \"Could not open file %s.\"|\"Load Game Error\"

int FUN_00461e9c(LPCSTR param_1,byte *param_2)

{
  HANDLE hFile;
  DWORD DVar1;
  BOOL BVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  CHAR local_108 [256];
  DWORD local_8;
  
  iVar5 = 0;
  hFile = CreateFileA(param_1,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000000,(HANDLE)0x0);
  if ((hFile != (HANDLE)0xffffffff) &&
     (DVar1 = SetFilePointer(hFile,0x15c,(PLONG)0x0,0), DVar1 != 0xffffffff)) {
    BVar2 = ReadFile(hFile,&DAT_0059f160,0x13e8,&local_8,(LPOVERLAPPED)0x0);
    if (BVar2 != 0) {
      *param_2 = 0;
      iVar4 = 0;
      pcVar3 = &DAT_0059f161;
      do {
        if ('\0' < *pcVar3) {
          iVar5 = iVar5 + 1;
          *param_2 = *param_2 | '\x01' << (pcVar3[1] & 0x1fU);
        }
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 0x2d8;
      } while (iVar4 < 7);
    }
    CloseHandle(hFile);
    return iVar5;
  }
  wsprintfA(local_108,PTR_s_Could_not_open_file__s__00509a04,param_1);
  FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_108,4,0,0);
  if (hFile != (HANDLE)0x0) {
    CloseHandle(hFile);
  }
  return -1;
}

