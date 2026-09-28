// FUN_0048a766 @ 0048a766 size=72 sig=undefined FUN_0048a766() cc=unknown
// callers: FUN_00482ba0
// callees: ReleaseMutex,WaitForSingleObject

bool FUN_0048a766(int param_1,undefined4 param_2)

{
  DWORD DVar1;
  bool bVar2;
  
  if (param_1 == 0) {
    bVar2 = false;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      bVar2 = false;
    }
    else {
      bVar2 = *(int *)(param_1 + 0x4c) != 0;
      if (bVar2) {
        *(undefined4 *)(param_1 + 100) = param_2;
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return bVar2;
}

