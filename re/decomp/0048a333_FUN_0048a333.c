// FUN_0048a333 @ 0048a333 size=188 sig=undefined FUN_0048a333() cc=unknown
// callers: FUN_00482ba0,FUN_00482d3c,FUN_004a1555
// callees: GetTickCount,ReleaseMutex,WaitForSingleObject

undefined4 FUN_0048a333(int param_1,int param_2)

{
  DWORD DVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_8;
  
  local_8 = 0;
  uVar3 = 0;
  if (DAT_0051b5fc != 0) {
    if (param_1 == 0) {
      uVar3 = 0;
    }
    else {
      DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
      if (DVar1 == 0xffffffff) {
        uVar3 = 0;
      }
      else {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x24))(*(int **)(param_1 + 0x44),&local_8)
        ;
        if (iVar2 == 0) {
          if ((local_8 & 1) == 1) {
            iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x34))(*(int **)(param_1 + 0x44),0);
            if (iVar2 == 0) {
              DVar1 = GetTickCount();
              *(DWORD *)(param_1 + 0x10) = DVar1;
              uVar3 = 1;
            }
          }
          else {
            iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x30))
                              (*(int **)(param_1 + 0x44),0,0,param_2 != 0);
            if (iVar2 == 0) {
              DVar1 = GetTickCount();
              *(DWORD *)(param_1 + 0x10) = DVar1;
              *(undefined4 *)(param_1 + 0x24) = 0;
              *(int *)(param_1 + 0x28) = param_2;
              uVar3 = 1;
            }
          }
        }
        ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
      }
    }
  }
  return uVar3;
}

