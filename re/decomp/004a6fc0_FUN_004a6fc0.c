// FUN_004a6fc0 @ 004a6fc0 size=111 sig=undefined FUN_004a6fc0() cc=unknown
// callers: 
// callees: FUN_004a9090,FUN_004b2fd4,FUN_004b02a8,FUN_004b2e1c

int * FUN_004a6fc0(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_2c;
  
  FUN_004a9090();
  if (param_2 != param_1) {
    FUN_004b2fd4(*param_1,3);
    iVar1 = FUN_004b02a8(4);
    if (iVar1 != 0) {
      FUN_004b2e1c(iVar1,*param_2);
    }
    *param_1 = iVar1;
  }
  *unaff_FS_OFFSET = local_2c;
  return param_1;
}

