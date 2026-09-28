// FUN_004a6c88 @ 004a6c88 size=67 sig=undefined FUN_004a6c88() cc=unknown
// callers: FUN_004b035c
// callees: FUN_004a9090,FUN_004a6e64

int FUN_004a6c88(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  FUN_004a6e64(param_1,param_2);
  *(undefined4 *)(param_1 + 4) = param_3;
  *unaff_FS_OFFSET = local_28;
  return param_1;
}

