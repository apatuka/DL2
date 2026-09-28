// FUN_004a240f @ 004a240f size=137 sig=undefined FUN_004a240f() cc=unknown
// callers: FUN_004a2cb5
// callees: 

int FUN_004a240f(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((((param_2 != 0) && (param_1 != 0)) && (*(int *)(param_1 + 300) != 0)) &&
     (**(int **)(param_1 + 300) != 0)) {
    for (iVar1 = **(int **)(param_1 + 300); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (((0 < *(int *)(iVar1 + 0x104)) && (*(int *)(iVar1 + 0x2c) != 0)) &&
         ((*(byte *)(iVar1 + 0x28) & 4) == 0)) {
        if ((((*(byte *)(iVar1 + 0x2e) & 4) == 0) && (0x20 < (*(uint *)(iVar1 + 0x2c) & 0xffff))) &&
           ((*(uint *)(iVar1 + 0x2c) & 0xffff) < 0x100)) {
          uVar2 = 0xfffbffff;
        }
        else {
          uVar2 = 0xffffffff;
        }
        if ((uVar2 & param_2) == *(uint *)(iVar1 + 0x2c)) {
          return iVar1;
        }
      }
    }
  }
  return 0;
}

