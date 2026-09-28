// FUN_004b2e1c @ 004b2e1c size=52 sig=undefined FUN_004b2e1c() cc=unknown
// callers: FUN_004a6ec4,FUN_004a6e64,FUN_004a6fc0
// callees: FUN_004a9090

undefined4 * FUN_004b2e1c(undefined4 *param_1,undefined4 *param_2)

{
  short *psVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  psVar1 = (short *)*param_2;
  *param_1 = psVar1;
  *psVar1 = *psVar1 + 1;
  *unaff_FS_OFFSET = local_28;
  return param_1;
}

