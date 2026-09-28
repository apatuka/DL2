// FUN_0048a2a6 @ 0048a2a6 size=112 sig=undefined FUN_0048a2a6() cc=unknown
// callers: FUN_00495fc5
// callees: CloseHandle,FUN_0048fbbf,WaitForSingleObject,timeKillEvent,timeEndPeriod

void FUN_0048a2a6(int param_1)

{
  DWORD DVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x48) != 0)) {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 != 0xffffffff) {
      if (*(int *)(param_1 + 0x4c) != 0) {
        timeKillEvent(*(UINT *)(param_1 + 0x4c));
        timeEndPeriod(0x32);
      }
      CloseHandle(*(HANDLE *)(param_1 + 0x48));
      *(undefined4 *)(param_1 + 0x48) = 0;
      if (*(int *)(param_1 + 0x34) != 0) {
        FUN_0048fbbf(*(undefined4 *)(param_1 + 0x34),1);
        *(undefined4 *)(param_1 + 0x34) = 0;
      }
      if (*(int *)(param_1 + 0x44) != 0) {
        (**(code **)(**(int **)(param_1 + 0x44) + 8))(*(int **)(param_1 + 0x44));
        *(undefined4 *)(param_1 + 0x44) = 0;
      }
    }
  }
  return;
}

