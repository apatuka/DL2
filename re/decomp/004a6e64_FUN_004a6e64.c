// FUN_004a6e64 @ 004a6e64 size=95 sig=undefined FUN_004a6e64() cc=unknown
// callers: FUN_004b3028,FUN_004a6c88,FUN_004b3168,FUN_004b30c8
// callees: FUN_004a9090,FUN_004b02a8,FUN_004b2e1c

int * FUN_004a6e64(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_2c;
  
  FUN_004a9090();
  iVar1 = FUN_004b02a8(4);
  if (iVar1 != 0) {
    FUN_004b2e1c(iVar1,param_2);
  }
  *param_1 = iVar1;
  *unaff_FS_OFFSET = local_2c;
  return param_1;
}

