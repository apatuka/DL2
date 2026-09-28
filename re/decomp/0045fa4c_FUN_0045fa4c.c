// FUN_0045fa4c @ 0045fa4c size=149 sig=undefined FUN_0045fa4c() cc=unknown
// callers: ChCht
// callees: WriteFile

undefined4 FUN_0045fa4c(HANDLE param_1)

{
  LPCVOID lpBuffer;
  BOOL BVar1;
  undefined4 uVar2;
  undefined4 local_c;
  DWORD local_8;
  
  BVar1 = WriteFile(param_1,&DAT_0059f160,0x13e8,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    uVar2 = 0;
  }
  else {
    local_c = 0xffffffff;
    for (lpBuffer = (LPCVOID)(&DAT_0059f19a)[DAT_0058f1f4 * 0xb6]; lpBuffer != (LPCVOID)0x0;
        lpBuffer = *(LPCVOID *)((int)lpBuffer + 4)) {
      BVar1 = WriteFile(param_1,lpBuffer,4,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
    }
    BVar1 = WriteFile(param_1,&local_c,4,&local_8,(LPOVERLAPPED)0x0);
    if (BVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

