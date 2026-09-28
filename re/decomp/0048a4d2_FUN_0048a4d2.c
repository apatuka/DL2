// FUN_0048a4d2 @ 0048a4d2 size=106 sig=undefined FUN_0048a4d2() cc=unknown
// callers: FUN_00482cec
// callees: ReleaseMutex,FUN_0048fa92,WaitForSingleObject

bool FUN_0048a4d2(int param_1,int *param_2)

{
  DWORD DVar1;
  int iVar2;
  bool bVar3;
  undefined1 local_8 [4];
  
  if (param_1 == 0) {
    bVar3 = false;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      bVar3 = false;
    }
    else {
      if (*(int *)(param_1 + 0x34) == 0) {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x10))
                          (*(int **)(param_1 + 0x44),param_2,local_8);
        bVar3 = -1 < iVar2;
      }
      else {
        iVar2 = FUN_0048fa92(*(undefined4 *)(param_1 + 0x34));
        *param_2 = iVar2 - *(int *)(param_1 + 0x38);
        bVar3 = true;
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return bVar3;
}

