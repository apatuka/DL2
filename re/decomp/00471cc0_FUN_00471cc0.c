// FUN_00471cc0 @ 00471cc0 size=41 sig=undefined FUN_00471cc0() cc=unknown
// callers: FUN_0046aa10,WriteUnitData,ProduceUnits,FUN_004720f4,FUN_0041c418,SetItemStats,FUN_0041ffd4,FUN_00471e58,FUN_00471cec
// callees: 

int FUN_00471cc0(int param_1)

{
  return *(int *)(param_1 + 0x1c) * 10 + *(int *)(param_1 + 0x14) * 5 + *(int *)(param_1 + 0x18) * 5
         + *(int *)(param_1 + 0x10);
}

