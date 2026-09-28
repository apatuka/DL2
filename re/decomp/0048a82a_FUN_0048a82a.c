// FUN_0048a82a @ 0048a82a size=153 sig=undefined FUN_0048a82a() cc=unknown
// callers: 
// callees: FUN_0048a06a,FUN_004ae068,timeGetTime,FUN_0048a3ef

void FUN_0048a82a(int param_1)

{
  DWORD DVar1;
  int iVar2;
  
  DVar1 = timeGetTime();
  if (DVar1 - *(int *)(param_1 + 0x58) < *(uint *)(param_1 + 0x5c)) {
    iVar2 = FUN_004ae068();
    iVar2 = *(int *)(param_1 + 0x50) + iVar2;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x54);
  }
  FUN_0048a06a(param_1,iVar2);
  if (iVar2 == *(int *)(param_1 + 0x54)) {
    *(undefined4 *)(param_1 + 0x58) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    if (*(int *)(param_1 + 0x60) != 0) {
      FUN_0048a3ef(param_1);
    }
  }
  return;
}

