// FUN_004a6f28 @ 004a6f28 size=65 sig=undefined FUN_004a6f28() cc=unknown
// callers: FUN_004a6dd9,FUN_004b03bc
// callees: FUN_004a9090,free,FUN_004b2fd4

void FUN_004a6f28(undefined4 *param_1,byte param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  if (param_1 != (undefined4 *)0x0) {
    FUN_004b2fd4(*param_1,3);
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

