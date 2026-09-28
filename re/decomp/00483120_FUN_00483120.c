// FUN_00483120 @ 00483120 size=135 sig=undefined FUN_00483120() cc=unknown
// callers: LoadPhaseSpriteFile
// callees: SetFilePointer,FUN_00483038,ReadFile

DWORD FUN_00483120(HANDLE param_1,int param_2,LPVOID param_3)

{
  DWORD nNumberOfBytesToRead;
  DWORD DVar1;
  DWORD local_8;
  
  if (*(short *)(param_2 + 4) == 0) {
    nNumberOfBytesToRead = 0;
  }
  else {
    nNumberOfBytesToRead = (int)*(short *)(param_2 + 0x14) * (int)*(short *)(param_2 + 0x16);
    DVar1 = SetFilePointer(param_1,*(LONG *)(param_2 + 0x1c),(PLONG)0x0,0);
    if (DVar1 == *(DWORD *)(param_2 + 0x1c)) {
      ReadFile(param_1,param_3,nNumberOfBytesToRead,&local_8,(LPOVERLAPPED)0x0);
      if (nNumberOfBytesToRead - local_8 == 0) {
        *(LPVOID *)(param_2 + 8) = param_3;
        FUN_00483038(param_2);
        while (*(short *)(param_2 + 0x14) != 0) {
          *(undefined4 *)(param_2 + 0x18) = 0;
          param_2 = param_2 + 0x10;
        }
      }
      else {
        nNumberOfBytesToRead = 0;
      }
    }
    else {
      nNumberOfBytesToRead = 0;
    }
  }
  return nNumberOfBytesToRead;
}

