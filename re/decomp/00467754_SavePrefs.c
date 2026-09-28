// SavePrefs @ 00467754 size=103 sig=undefined SavePrefs() cc=unknown
// callers: WinMain,ShutdownGame
// callees: LoadPrefs,FUN_004671d8,WriteFile,CloseHandle,CreateFileA
// strings: \"DL2.PRF\"

/* Writes DL2.PRF */

undefined8 SavePrefs(void)

{
  int iVar1;
  HANDLE hFile;
  DWORD local_8;
  
  iVar1 = FUN_004671d8(&DAT_0058eca8);
  if (iVar1 == 0) {
    LoadPrefs();
  }
  hFile = CreateFileA(s_DL2_PRF_004d5134,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x8000000,
                      (HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffff) {
    WriteFile(hFile,&DAT_0058eca8,0x86,&local_8,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return CONCAT44(local_8,(uint)(local_8 == 0x86));
}

