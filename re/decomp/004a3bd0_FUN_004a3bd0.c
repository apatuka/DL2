// FUN_004a3bd0 @ 004a3bd0 size=248 sig=undefined FUN_004a3bd0() cc=unknown
// callers: FUN_004a3cc8
// callees: FUN_004a110f,FUN_004a118a

void FUN_004a3bd0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar1 = FUN_004a110f(param_1,0);
  if (iVar1 != 0) {
    local_1c = *(int *)(iVar1 + 0xc);
    local_18 = *(int *)(iVar1 + 0x10);
    local_14 = *(int *)(iVar1 + 0xc) + *(int *)(iVar1 + 0x18);
    local_10 = *(int *)(iVar1 + 0x10) + *(int *)(iVar1 + 0x14);
    iVar1 = 1;
    while( true ) {
      iVar4 = iVar1 + 1;
      iVar2 = FUN_004a110f(param_1,iVar1);
      if (iVar2 == 0) break;
      if (*(int *)(iVar2 + 0xc) < local_1c) {
        local_1c = *(int *)(iVar2 + 0xc);
      }
      if (*(int *)(iVar2 + 0x10) < local_18) {
        local_18 = *(int *)(iVar2 + 0x10);
      }
      if (local_14 < *(int *)(iVar2 + 0xc) + *(int *)(iVar2 + 0x18)) {
        local_14 = *(int *)(iVar2 + 0xc) + *(int *)(iVar2 + 0x18);
      }
      iVar1 = iVar4;
      if (local_10 < *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 0x14)) {
        local_10 = *(int *)(iVar2 + 0x10) + *(int *)(iVar2 + 0x14);
      }
    }
    iVar4 = *(int *)(param_1 + 8) + local_1c;
    iVar2 = *(int *)(param_1 + 0xc) + local_18;
    iVar1 = 0;
    while( true ) {
      iVar3 = FUN_004a110f(param_1,iVar1);
      if (iVar3 == 0) break;
      FUN_004a118a(iVar3,-iVar4,-iVar2,0);
      iVar1 = iVar1 + 1;
    }
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + iVar4;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + iVar2;
    *(int *)(param_1 + 0x14) = local_14 - local_1c;
    *(int *)(param_1 + 0x10) = local_10 - local_18;
  }
  return;
}

