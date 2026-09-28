// FUN_004952f0 @ 004952f0 size=171 sig=undefined FUN_004952f0() cc=unknown
// callers: 
// callees: FUN_004888ec,FUN_00488c95,SetEndOfFile,FUN_00488ba3,FUN_00488a09,FUN_0049512a
// strings: \"err.log\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004952f0(void)

{
  bool bVar1;
  HANDLE hFile;
  int iVar2;
  undefined1 local_10c [263];
  char local_5;
  
  bVar1 = false;
  if ((_DAT_0051dcc4 & 0x80000000) != 0) {
    _DAT_0051dcc4 = _DAT_0051dcc4 & 0x7fffffff;
    FUN_0049512a(local_10c,s_err_log_0051e071);
    hFile = (HANDLE)FUN_004888ec(local_10c,2);
    if (hFile != (HANDLE)0xffffffff) {
      iVar2 = FUN_00488c95(hFile,0,2);
      while (0 < iVar2) {
        iVar2 = FUN_00488c95(hFile,iVar2 + -1,0);
        FUN_00488ba3(hFile,&local_5,1);
        if ((local_5 == '\r') || (local_5 == '\n')) {
          if (bVar1) break;
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
      }
      SetEndOfFile(hFile);
      FUN_00488a09(hFile);
    }
    _DAT_0051dcc4 = _DAT_0051dcc4 | 0x80000000;
  }
  return;
}

