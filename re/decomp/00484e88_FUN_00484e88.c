// FUN_00484e88 @ 00484e88 size=28 sig=undefined FUN_00484e88() cc=unknown
// callers: SendTerritoryData,FUN_0044bd0c,FUN_004607d8,FUN_0044c49c,FUN_0044bc68,FUN_0040f8cc
// callees: 

int FUN_00484e88(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *param_1; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x30)) {
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

