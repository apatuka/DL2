// FUN_00411cdc @ 00411cdc size=73 sig=undefined FUN_00411cdc() cc=unknown
// callers: FUN_00412584
// callees: free,FUN_00411720,FUN_0048d07b

void FUN_00411cdc(undefined4 *param_1,byte param_2)

{
  int iVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_FUN_004b6fc0;
    for (iVar1 = param_1[1]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1a)) {
      FUN_0048d07b(*(undefined4 *)(iVar1 + 10));
      *(undefined4 *)(iVar1 + 10) = 0;
    }
    FUN_00411720(param_1,0);
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  return;
}

