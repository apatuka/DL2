// FUN_004b335c @ 004b335c size=83 sig=undefined FUN_004b335c() cc=unknown
// callers: 
// callees: FUN_004a9090,FUN_004b3400,FUN_004b1010

void FUN_004b335c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  iVar1 = FUN_004b3400(*(undefined4 *)(param_1 + 6));
  if (DAT_005217f4 < (uint)(*(int *)(param_1 + 10) - iVar1)) {
    uVar2 = FUN_004b1010(*(undefined4 *)(param_1 + 2),iVar1 + 1);
    *(undefined4 *)(param_1 + 2) = uVar2;
    *(int *)(param_1 + 10) = iVar1;
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

