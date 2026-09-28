// FUN_004a6dd9 @ 004a6dd9 size=70 sig=undefined FUN_004a6dd9() cc=unknown
// callers: 
// callees: FUN_004a9090,free,FUN_004a6f28

void FUN_004a6dd9(int param_1,byte param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  if (param_1 != 0) {
    FUN_004a6f28(param_1,0);
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

