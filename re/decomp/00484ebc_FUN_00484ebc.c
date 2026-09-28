// FUN_00484ebc @ 00484ebc size=34 sig=undefined FUN_00484ebc() cc=unknown
// callers: FUN_0044e0a8,SendTerritoryData,FUN_00405b38,FUN_0040f658,FUN_004607d8,FUN_0041d710,FUN_004488c8,FUN_0041c418,FUN_0041ffd4,FUN_0040f6b0,FUN_00420d34
// callees: 

bool FUN_00484ebc(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    *(undefined4 *)(param_1 + 4) = *(undefined4 *)(*(int *)(param_1 + 4) + 0x30);
  }
  return *(int *)(param_1 + 4) != 0;
}

