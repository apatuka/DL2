// FUN_0049f715 @ 0049f715 size=61 sig=undefined FUN_0049f715() cc=unknown
// callers: FUN_004a2ac6,FUN_004a2498,FUN_004a2cb5
// callees: 

int FUN_0049f715(int param_1)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if ((*(byte *)(iVar1 + 0x2a) & 0x80) != 0) {
        return iVar1;
      }
    }
  }
  return 0;
}

