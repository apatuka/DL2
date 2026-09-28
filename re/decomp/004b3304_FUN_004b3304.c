// FUN_004b3304 @ 004b3304 size=88 sig=undefined FUN_004b3304() cc=unknown
// callers: 
// callees: FUN_004a9090,FUN_004b3400,FUN_004b1010

void FUN_004b3304(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  *(uint *)(param_1 + 0xe) = *(uint *)(param_1 + 0xe) | 1;
  iVar1 = FUN_004b3400(param_2 + 1);
  if (DAT_005217f4 < (uint)(*(int *)(param_1 + 10) - iVar1)) {
    uVar2 = FUN_004b1010(*(undefined4 *)(param_1 + 2),iVar1 + 1);
    *(undefined4 *)(param_1 + 2) = uVar2;
    *(int *)(param_1 + 10) = iVar1;
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

