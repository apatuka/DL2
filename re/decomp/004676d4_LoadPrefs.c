// LoadPrefs @ 004676d4 size=126 sig=undefined LoadPrefs() cc=unknown
// callers: SavePrefs,LoadPrefsAndInit
// callees: FUN_004671d8,ReadFile,CloseHandle,CreateFileA,ParsePrefs
// strings: \"DL2.PRF\"

/* Reads DL2.PRF (134 bytes) and validates */

void LoadPrefs(void)

{
  HANDLE hFile;
  int iVar1;
  DWORD local_c;
  
  iVar1 = 0;
  hFile = CreateFileA(s_DL2_PRF_004d5134,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x8000000,
                      (HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffff) {
    ReadFile(hFile,&DAT_0058eca8,0x86,&local_c,(LPOVERLAPPED)0x0);
    if ((local_c == 0x86) && (DAT_0058eca8 == DAT_004d5ae8)) {
      iVar1 = ParsePrefs(&DAT_0058eca8);
    }
    CloseHandle(hFile);
  }
  if (iVar1 == 0) {
    FUN_004671d8(&DAT_0058eca8);
  }
  return;
}

