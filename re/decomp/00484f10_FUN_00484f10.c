// FUN_00484f10 @ 00484f10 size=25 sig=undefined FUN_00484f10() cc=unknown
// callers: SendTerritoryData,FUN_0040f658,FUN_004607d8,FUN_004488c8,FUN_0041c418,FUN_0041ffd4
// callees: 

undefined2 FUN_00484f10(int param_1)

{
  undefined2 uVar1;
  
  if (*(int *)(param_1 + 4) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 4) + 2);
  }
  return uVar1;
}

