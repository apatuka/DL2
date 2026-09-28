// FUN_0049f8dd @ 0049f8dd size=106 sig=undefined FUN_0049f8dd() cc=unknown
// callers: FUN_0049f947
// callees: FUN_0049f8a1,FUN_0049f64c

void FUN_0049f8dd(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (((*(int *)(iVar1 + 0x1c) == 2) && (param_2 == *(int *)(iVar1 + 0x20))) &&
         (iVar2 = FUN_0049f64c(iVar1), iVar2 != 0)) {
        FUN_0049f8a1(iVar1,0);
      }
    }
  }
  if (param_3 != 0) {
    FUN_0049f8a1(param_3,1);
  }
  return;
}

