// FUN_0048a3ef @ 0048a3ef size=81 sig=undefined FUN_0048a3ef() cc=unknown
// callers: FUN_00495fc5,FUN_00482edc,FUN_00496024,FUN_0049604c,FUN_00482cec,FUN_00482e84,FUN_0048a82a,FUN_004a1555,FUN_00496093
// callees: ReleaseMutex,WaitForSingleObject

bool FUN_0048a3ef(int param_1)

{
  DWORD DVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = false;
  if (DAT_0051b5fc != 0) {
    if (param_1 == 0) {
      bVar3 = false;
    }
    else {
      DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
      if (DVar1 == 0xffffffff) {
        bVar3 = false;
      }
      else {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x48))(*(int **)(param_1 + 0x44));
        bVar3 = iVar2 == 0;
        ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
      }
    }
  }
  return bVar3;
}

