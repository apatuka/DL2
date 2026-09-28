// FUN_0048a8c3 @ 0048a8c3 size=177 sig=undefined FUN_0048a8c3() cc=unknown
// callers: 
// callees: FUN_0048a145,FUN_0048fb67,FUN_0048fade

void FUN_0048a8c3(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 local_c [4];
  uint local_8;
  
  (**(code **)(**(int **)(param_1 + 0x44) + 0x10))(*(int **)(param_1 + 0x44),&local_8,local_c);
  if (local_8 != *(uint *)(param_1 + 0x40)) {
    if (local_8 < *(uint *)(param_1 + 0x40)) {
      iVar2 = *(int *)(param_1 + 8) - (*(int *)(param_1 + 0x40) - local_8);
    }
    else {
      iVar2 = local_8 - *(int *)(param_1 + 0x40);
    }
    iVar1 = FUN_0048fb67(*(undefined4 *)(param_1 + 0x34));
    if (iVar1 == 0) {
      if (*(int *)(param_1 + 0x28) == 0) {
        iVar1 = FUN_0048a145(param_1,*(undefined4 *)(param_1 + 0x40),iVar2,0,0);
        iVar2 = iVar2 + iVar1;
      }
      else {
        FUN_0048fade(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x38),0);
        iVar2 = FUN_0048a145(param_1,*(undefined4 *)(param_1 + 0x40),iVar2,
                             *(undefined4 *)(param_1 + 0x34),0);
      }
    }
    else {
      iVar2 = FUN_0048a145(param_1,*(undefined4 *)(param_1 + 0x40),iVar2,
                           *(undefined4 *)(param_1 + 0x34),0);
    }
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + iVar2;
    if (*(uint *)(param_1 + 8) <= *(uint *)(param_1 + 0x40)) {
      *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) - *(int *)(param_1 + 8);
    }
  }
  return;
}

