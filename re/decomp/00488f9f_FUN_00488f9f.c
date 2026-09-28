// FUN_00488f9f @ 00488f9f size=189 sig=undefined FUN_00488f9f() cc=unknown
// callers: 
// callees: GetTickCount,CloseHandle,FUN_004989cf,FUN_00498ba9,GetFileSize,ReadFile,CreateFileA

/* WARNING: Removing unreachable block (ram,0x00488ff1) */

int FUN_00488f9f(LPCSTR param_1,uint param_2)

{
  HANDLE hFile;
  DWORD DVar1;
  uint nNumberOfBytesToRead;
  BOOL BVar2;
  DWORD DVar3;
  int iVar4;
  uint uVar5;
  DWORD local_14;
  uint local_10;
  DWORD local_c;
  LPVOID local_8;
  
  iVar4 = 0;
  local_8 = (LPVOID)FUN_00498ba9(param_2);
  if (local_8 != (LPVOID)0x0) {
    hFile = CreateFileA(param_1,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffff) {
      local_10 = 0;
      GetFileSize(hFile,&local_14);
      uVar5 = 0;
      DVar1 = GetTickCount();
      while( true ) {
        nNumberOfBytesToRead = uVar5;
        if (param_2 < uVar5) {
          nNumberOfBytesToRead = param_2;
        }
        BVar2 = ReadFile(hFile,local_8,nNumberOfBytesToRead,&local_c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) break;
        local_10 = local_10 + local_c;
        uVar5 = uVar5 - local_c;
        if ((local_c == 0) || (uVar5 == 0)) break;
      }
      DVar3 = GetTickCount();
      CloseHandle(hFile);
      iVar4 = (local_10 / (DVar3 - DVar1)) * 1000;
    }
    FUN_004989cf(local_8);
  }
  return iVar4;
}

