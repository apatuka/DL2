// FUN_0049d18d @ 0049d18d size=80 sig=undefined FUN_0049d18d() cc=unknown
// callers: FUN_0049eef7
// callees: FUN_004954a9,FUN_004954f9,FUN_004989cf

undefined4 FUN_0049d18d(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (*(int *)(param_2 + 0x94) != 0) {
    iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3);
    if (iVar1 != 0) {
      FUN_004954a9(*(undefined4 *)(param_2 + 0x94),iVar1);
      if (*(int *)(iVar1 + 0x10) != 0) {
        FUN_004989cf(*(undefined4 *)(iVar1 + 0x10));
      }
      FUN_004989cf(iVar1);
    }
  }
  return 1;
}

