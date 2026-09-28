// FUN_00495544 @ 00495544 size=28 sig=undefined FUN_00495544() cc=unknown
// callers: FUN_004a3d26,FUN_0049d7cc,FUN_004a4025,FUN_0049d105
// callees: 

int FUN_00495544(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *param_1; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

