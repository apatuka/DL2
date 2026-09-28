// FUN_004620dc @ 004620dc size=33 sig=undefined FUN_004620dc() cc=unknown
// callers: FUN_0045f664
// callees: WriteFile

void FUN_004620dc(HANDLE param_1)

{
  DWORD local_8;
  
  WriteFile(param_1,&stack0x00000008,0xac,&local_8,(LPOVERLAPPED)0x0);
  return;
}

