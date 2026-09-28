// FUN_0048a6fa @ 0048a6fa size=108 sig=undefined FUN_0048a6fa() cc=unknown
// callers: 
// callees: ReleaseMutex,WaitForSingleObject,FUN_0048a021,timeGetTime

bool FUN_0048a6fa(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  DWORD DVar1;
  int iVar2;
  bool bVar3;
  undefined4 local_8;
  
  if (param_1 == 0) {
    bVar3 = false;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      bVar3 = false;
    }
    else {
      iVar2 = FUN_0048a021(param_1,&local_8);
      bVar3 = iVar2 != 0;
      if (bVar3) {
        *(undefined4 *)(param_1 + 0x50) = local_8;
        *(undefined4 *)(param_1 + 0x54) = param_2;
        DVar1 = timeGetTime();
        *(DWORD *)(param_1 + 0x58) = DVar1;
        *(undefined4 *)(param_1 + 0x5c) = param_3;
        *(undefined4 *)(param_1 + 0x60) = param_4;
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return bVar3;
}

