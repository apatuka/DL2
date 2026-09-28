// FUN_0048a53c @ 0048a53c size=225 sig=undefined FUN_0048a53c() cc=unknown
// callers: FUN_00482d3c
// callees: FUN_0048fade,ReleaseMutex,WaitForSingleObject,FUN_0048a145

bool FUN_0048a53c(int param_1,int param_2)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  uint local_c;
  uint local_8;
  
  if (param_1 == 0) {
    bVar4 = false;
  }
  else {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 == 0xffffffff) {
      bVar4 = false;
    }
    else {
      if (*(int *)(param_1 + 0x34) == 0) {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x34))(*(int **)(param_1 + 0x44),param_2);
        bVar4 = -1 < iVar2;
      }
      else {
        FUN_0048fade(*(undefined4 *)(param_1 + 0x34),param_2 + *(int *)(param_1 + 0x38),0);
        iVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0x10))
                          (*(int **)(param_1 + 0x44),&local_c,&local_8);
        if (iVar2 < 0) {
          bVar4 = false;
        }
        else {
          if (local_c < local_8) {
            iVar2 = *(int *)(param_1 + 8) - (local_8 - local_c);
          }
          else {
            iVar2 = local_c - local_8;
          }
          iVar2 = FUN_0048a145(param_1,local_8,iVar2,*(undefined4 *)(param_1 + 0x34),0);
          iVar3 = (**(code **)(**(int **)(param_1 + 0x44) + 0x34))
                            (*(int **)(param_1 + 0x44),local_8);
          if (iVar3 < 0) {
            bVar4 = false;
          }
          else {
            *(uint *)(param_1 + 0x40) = iVar2 + local_8;
            if (*(uint *)(param_1 + 8) < *(uint *)(param_1 + 0x40)) {
              *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) - *(int *)(param_1 + 8);
            }
            bVar4 = true;
          }
        }
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return bVar4;
}

