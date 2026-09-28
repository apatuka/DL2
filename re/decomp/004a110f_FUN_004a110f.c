// FUN_004a110f @ 004a110f size=65 sig=undefined FUN_004a110f() cc=unknown
// callers: FUN_004a1150,FUN_004a3bd0
// callees: 

int FUN_004a110f(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    iVar2 = 0;
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (iVar2 == param_2) {
        return iVar1;
      }
      iVar2 = iVar2 + 1;
    }
  }
  return 0;
}

