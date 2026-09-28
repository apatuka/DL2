// FUN_0048a021 @ 0048a021 size=73 sig=undefined FUN_0048a021() cc=unknown
// callers: FUN_0048a6fa
// callees: ReleaseMutex,WaitForSingleObject

bool FUN_0048a021(int param_1,undefined4 param_2)

{
  DWORD DVar1;
  int iVar2;
  bool bVar3;
  
  if (param_1 == 0) {
    bVar3 = false;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      bVar3 = false;
    }
    else {
      iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x18))(*(int **)(param_1 + 0x44),param_2);
      bVar3 = iVar2 == 0;
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return bVar3;
}

