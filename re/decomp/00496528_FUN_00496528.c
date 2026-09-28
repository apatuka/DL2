// FUN_00496528 @ 00496528 size=71 sig=undefined FUN_00496528() cc=unknown
// callers: FUN_00496748
// callees: FUN_004989cf

void FUN_00496528(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  if (param_1 != 0) {
    iVar2 = param_1 + 0x18;
    local_8 = *(int *)(param_1 + 0x14);
    while (local_8 != 0) {
      iVar1 = *(int *)(iVar2 + 4) + param_1;
      if (*(int *)(iVar1 + 8) != 0) {
        FUN_004989cf(*(undefined4 *)(iVar1 + 8));
        *(undefined4 *)(iVar1 + 8) = 0;
      }
      iVar2 = iVar2 + 8;
      local_8 = local_8 + -1;
    }
  }
  return;
}

