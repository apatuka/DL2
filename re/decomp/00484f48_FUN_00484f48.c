// FUN_00484f48 @ 00484f48 size=42 sig=undefined FUN_00484f48() cc=unknown
// callers: FUN_0044e0a8,SendTerritoryData,FUN_004607d8,FUN_0041c418,FUN_0041ffd4,ProduceUnits
// callees: 

void FUN_00484f48(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 4) != 0) {
    iVar2 = 0;
    do {
      iVar1 = iVar2 * 4;
      iVar2 = iVar2 + 1;
      *param_2 = *(undefined4 *)(*(int *)(param_1 + 4) + 4 + iVar1);
      param_2 = param_2 + 1;
    } while (iVar2 < 0xb);
  }
  return;
}

