// FUN_0048a667 @ 0048a667 size=147 sig=undefined FUN_0048a667() cc=unknown
// callers: FUN_00496199,FUN_004961e8
// callees: CreateMutexA,FUN_00495454,FUN_0048f7f1,FUN_004989cf,ReleaseMutex,FUN_00498ba9,WaitForSingleObject

int FUN_0048a667(int param_1)

{
  DWORD DVar1;
  int iVar2;
  HANDLE pvVar3;
  int iVar4;
  
  iVar4 = 0;
  if (DAT_0051b5fc != (int *)0x0) {
    DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x48),0xffffffff);
    if (DVar1 != 0xffffffff) {
      iVar4 = FUN_00498ba9(0x68);
      if (iVar4 != 0) {
        FUN_0048f7f1(param_1,iVar4,0x68);
        *(undefined4 *)(iVar4 + 0x44) = 0;
        iVar2 = (**(code **)(*DAT_0051b5fc + 0x14))
                          (DAT_0051b5fc,*(undefined4 *)(param_1 + 0x44),iVar4 + 0x44);
        if (iVar2 != 0) {
          FUN_004989cf(iVar4);
          iVar4 = 0;
        }
        *(uint *)(iVar4 + 0xc) = *(uint *)(iVar4 + 0xc) & 0xfffffff8;
        pvVar3 = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,(LPCSTR)0x0);
        *(HANDLE *)(iVar4 + 0x48) = pvVar3;
        FUN_00495454(DAT_0051e08c,iVar4,0);
        ReleaseMutex(*(HANDLE *)(iVar4 + 0x48));
      }
      ReleaseMutex(*(HANDLE *)(param_1 + 0x48));
    }
  }
  return iVar4;
}

