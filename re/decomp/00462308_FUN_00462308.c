// FUN_00462308 @ 00462308 size=30 sig=undefined FUN_00462308() cc=unknown
// callers: FUN_0045fa10
// callees: WriteFile

void FUN_00462308(HANDLE param_1)

{
  DWORD local_8;
  
  WriteFile(param_1,&stack0x00000008,0x14,&local_8,(LPOVERLAPPED)0x0);
  return;
}

