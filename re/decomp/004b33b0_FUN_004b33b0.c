// FUN_004b33b0 @ 004b33b0 size=78 sig=undefined FUN_004b33b0() cc=unknown
// callers: FUN_004b343c
// callees: FUN_004a9090,FUN_004a6ccc,FUN_004b1010

void FUN_004b33b0(int param_1,int param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  *(int *)(param_1 + 10) = param_2;
  iVar1 = FUN_004b1010(*(undefined4 *)(param_1 + 2),param_2 + 1);
  *(int *)(param_1 + 2) = iVar1;
  if (iVar1 == 0) {
    FUN_004a6ccc(&DAT_0052114c);
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

