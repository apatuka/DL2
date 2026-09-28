// FUN_00483098 @ 00483098 size=131 sig=undefined FUN_00483098() cc=unknown
// callers: LoadGlobalSprites,FUN_00483224,LoadPhaseSpriteFile
// callees: SetFilePointer,FUN_00483038,ReadFile

int FUN_00483098(HANDLE param_1,int param_2,LPVOID param_3)

{
  DWORD DVar1;
  DWORD nNumberOfBytesToRead;
  DWORD local_c;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(short *)(param_2 + 4) == 0) {
      return local_8;
    }
    nNumberOfBytesToRead = (int)*(short *)(param_2 + 4) * (int)*(short *)(param_2 + 6);
    DVar1 = SetFilePointer(param_1,*(LONG *)(param_2 + 0xc),(PLONG)0x0,0);
    if (DVar1 != *(DWORD *)(param_2 + 0xc)) break;
    ReadFile(param_1,param_3,nNumberOfBytesToRead,&local_c,(LPOVERLAPPED)0x0);
    if (nNumberOfBytesToRead - local_c != 0) {
      return 0;
    }
    *(LPVOID *)(param_2 + 8) = param_3;
    param_3 = (LPVOID)((int)param_3 + nNumberOfBytesToRead);
    local_8 = nNumberOfBytesToRead + local_8;
    FUN_00483038(param_2);
    param_2 = param_2 + 0x10;
  }
  return 0;
}

