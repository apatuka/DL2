// FUN_00484c40 @ 00484c40 size=51 sig=undefined FUN_00484c40() cc=unknown
// callers: FUN_0046e56c,ResetVariables,FUN_0047c128
// callees: free

void FUN_00484c40(int *param_1,byte param_2)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    while (iVar1 = *param_1, iVar1 != 0) {
      *param_1 = *(int *)(iVar1 + 0x30);
      free(iVar1);
    }
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  return;
}

