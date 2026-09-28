// FUN_0044c320 @ 0044c320 size=71 sig=undefined FUN_0044c320() cc=unknown
// callers: MoveLaborToHousingNoNet,NetReassignLaborByTask,FUN_00475ce8
// callees: FUN_0044ba40,FUN_0044ba18

undefined4 FUN_0044c320(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_2 + 0x18 + param_3 * 4) != 0) {
    iVar2 = FUN_0044ba18(param_4);
    iVar3 = FUN_0044ba40(param_4);
    if ((iVar2 < iVar3) || (param_4 == param_2)) {
      piVar1 = (int *)(param_2 + 0x18 + param_3 * 4);
      *piVar1 = *piVar1 + -1;
      piVar1 = (int *)(param_4 + 0x18 + param_5 * 4);
      *piVar1 = *piVar1 + 1;
      return 1;
    }
  }
  return 0;
}

