// FUN_004b2fd4 @ 004b2fd4 size=81 sig=undefined FUN_004b2fd4() cc=unknown
// callers: FUN_004b3168,FUN_004a6f28,FUN_004b3028,FUN_004b30c8,FUN_004b035c,FUN_004a6fc0
// callees: free,FUN_004a9090,FUN_004b32c0

void FUN_004b2fd4(undefined4 *param_1,byte param_2)

{
  short *psVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  if (param_1 != (undefined4 *)0x0) {
    psVar1 = (short *)*param_1;
    *psVar1 = *psVar1 + -1;
    if (*psVar1 == 0) {
      FUN_004b32c0(*param_1,3);
    }
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

