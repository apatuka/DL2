// FUN_004b1570 @ 004b1570 size=223 sig=undefined FUN_004b1570() cc=unknown
// callers: __assertfail,FUN_004b1660,FUN_004afbe4,FUN_004b17c0,FUN_004b1650
// callees: FUN_004b1528,MessageBoxA,strlen,GetModuleFileNameA,FUN_004b01d4,FUN_004b16d8,GetStdHandle,WriteFile

void FUN_004b1570(LPCSTR param_1)

{
  int iVar1;
  uint uVar2;
  HANDLE hFile;
  DWORD nNumberOfBytesToWrite;
  LPCSTR lpCaption;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  CHAR local_58 [80];
  DWORD local_8;
  
  if (DAT_00521270 == (char *)0x0) {
    if (DAT_004b5062 != '\0') {
      GetModuleFileNameA((HMODULE)0x0,local_58,0x50);
      iVar1 = FUN_004b01d4(local_58,0x5c);
      if ((iVar1 == 0) && (iVar1 = FUN_004b01d4(local_58,0x3a), iVar1 == 0)) {
        lpCaption = local_58;
      }
      else {
        lpCaption = (LPCSTR)(iVar1 + 1);
      }
      uVar2 = FUN_004b1528();
      MessageBoxA((HWND)0x0,param_1,lpCaption,uVar2 | 0x10010);
      return;
    }
    hFile = GetStdHandle(0xfffffff4);
    WriteFile(hFile,&DAT_00521274,2,&local_8,(LPOVERLAPPED)0x0);
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &local_8;
    nNumberOfBytesToWrite = strlen(param_1);
    WriteFile(hFile,param_1,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    WriteFile(hFile,&DAT_00521277,2,&local_8,(LPOVERLAPPED)0x0);
    return;
  }
  if (DAT_00521270 == (char *)0xffffffff) {
    return;
  }
  if (DAT_00521270 == (char *)0x0) {
    return;
  }
  if (*DAT_00521270 == '\0') {
    return;
  }
  FUN_004b16d8(DAT_00521270,param_1);
  return;
}

