// FUN_004a1fc4 @ 004a1fc4 size=64 sig=undefined FUN_004a1fc4() cc=unknown
// callers: FUN_004a3cc8,FUN_004a2004
// callees: FUN_004a1eb4

void FUN_004a1fc4(int param_1)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      FUN_004a1eb4(param_1,iVar1);
    }
  }
  return;
}

