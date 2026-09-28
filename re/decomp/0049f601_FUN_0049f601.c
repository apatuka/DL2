// FUN_0049f601 @ 0049f601 size=75 sig=undefined FUN_0049f601() cc=unknown
// callers: 
// callees: 

int FUN_0049f601(int param_1,int param_2)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (((*(int *)(iVar1 + 0x1c) == 2) && (param_2 == *(int *)(iVar1 + 0x20))) &&
         ((*(byte *)(iVar1 + 0x28) & 1) != 0)) {
        return iVar1;
      }
    }
  }
  return 0;
}

