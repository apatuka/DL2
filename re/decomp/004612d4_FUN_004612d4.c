// FUN_004612d4 @ 004612d4 size=50 sig=undefined FUN_004612d4() cc=unknown
// callers: FUN_004618e8
// callees: ReadFile

BOOL FUN_004612d4(HANDLE param_1)

{
  BOOL BVar1;
  DWORD local_8;
  
  if (DAT_00583da4 < 3) {
    BVar1 = 1;
  }
  else {
    BVar1 = ReadFile(param_1,&DAT_00654804,700,&local_8,(LPOVERLAPPED)0x0);
  }
  return BVar1;
}

