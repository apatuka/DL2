// FUN_004a1457 @ 004a1457 size=114 sig=undefined FUN_004a1457() cc=unknown
// callers: FUN_004a14c9,FUN_004a1457
// callees: FUN_0049eb44,FUN_004a1457

void FUN_004a1457(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (DAT_0051e384 != (int *)0x0) {
      for (iVar1 = *DAT_0051e384; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
        FUN_004a1457(iVar1);
      }
    }
  }
  else if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      FUN_0049eb44(param_1,iVar1,2,0x3d,0x80,0);
    }
  }
  return;
}

