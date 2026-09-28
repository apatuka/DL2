// FUN_004b32c0 @ 004b32c0 size=65 sig=undefined FUN_004b32c0() cc=unknown
// callers: FUN_004b2fd4
// callees: free,FUN_004a9090,FUN_004b0a30

void FUN_004b32c0(int param_1,byte param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  if (param_1 != 0) {
    FUN_004b0a30(*(undefined4 *)(param_1 + 2));
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

