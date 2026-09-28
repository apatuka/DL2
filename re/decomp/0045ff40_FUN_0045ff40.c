// FUN_0045ff40 @ 0045ff40 size=81 sig=undefined FUN_0045ff40() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_0045ff40(HANDLE param_1)

{
  BOOL BVar1;
  undefined4 *lpBuffer;
  int iVar2;
  DWORD local_8;
  
  iVar2 = 0;
  do {
    for (lpBuffer = &DAT_00522280 + iVar2 * 0x11; lpBuffer != (undefined4 *)0x0;
        lpBuffer = (undefined4 *)lpBuffer[5]) {
      BVar1 = WriteFile(param_1,lpBuffer,0x44,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 7);
  return 1;
}

