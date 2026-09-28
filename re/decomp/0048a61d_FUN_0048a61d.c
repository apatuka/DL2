// FUN_0048a61d @ 0048a61d size=74 sig=undefined FUN_0048a61d() cc=unknown
// callers: FUN_004960fd,FUN_00496152,FUN_00496093,FUN_004a13e1
// callees: ReleaseMutex,WaitForSingleObject

undefined4 FUN_0048a61d(int param_1)

{
  DWORD DVar1;
  int iVar2;
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_8 = 0;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      local_8 = 0;
    }
    else {
      iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x24))(*(int **)(param_1 + 0x44),&local_8);
      if (iVar2 != 0) {
        local_8 = 0;
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return local_8;
}

