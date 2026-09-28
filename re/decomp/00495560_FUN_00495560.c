// FUN_00495560 @ 00495560 size=54 sig=undefined FUN_00495560() cc=unknown
// callers: 
// callees: FUN_004954a9,FUN_004989cf

undefined4 FUN_00495560(int *param_1)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    while (iVar1 != 0) {
      FUN_004954a9(param_1,iVar1);
      FUN_004989cf(iVar1);
      iVar1 = *param_1;
    }
    FUN_004989cf(param_1);
  }
  return 1;
}

