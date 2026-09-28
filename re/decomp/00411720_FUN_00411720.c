// FUN_00411720 @ 00411720 size=90 sig=undefined FUN_00411720() cc=unknown
// callers: FUN_00411cdc,FUN_00412584
// callees: free

void FUN_00411720(undefined4 *param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = &PTR_LAB_004b6fc8;
    if (param_1[2] != 0) {
      free(param_1[2]);
    }
    iVar2 = param_1[1];
    while (iVar2 != 0) {
      iVar1 = *(int *)(iVar2 + 0x1a);
      if (*(int *)(iVar2 + 10) != 0) {
        free(*(int *)(iVar2 + 10));
      }
      free(iVar2);
      iVar2 = iVar1;
    }
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  return;
}

