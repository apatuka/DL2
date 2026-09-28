// FUN_00461328 @ 00461328 size=64 sig=undefined FUN_00461328() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile,memset

BOOL FUN_00461328(HANDLE param_1)

{
  BOOL BVar1;
  DWORD local_8;
  
  if (DAT_00583da8 < 0x11) {
    memset(&DAT_00657df4,0,0x2a);
    BVar1 = 1;
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_00657df4,0x2a,&local_8,(LPOVERLAPPED)0x0);
  }
  return BVar1;
}

