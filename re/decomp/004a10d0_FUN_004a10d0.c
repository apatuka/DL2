// FUN_004a10d0 @ 004a10d0 size=63 sig=undefined FUN_004a10d0() cc=unknown
// callers: FUN_00429a04,FUN_0042a08c,FUN_004a1150,FUN_0042c934
// callees: 

int FUN_004a10d0(int param_1,int param_2)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (param_2 == *(int *)(iVar1 + 0x30)) {
        return iVar1;
      }
    }
  }
  return 0;
}

