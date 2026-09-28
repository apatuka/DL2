// FUN_00486734 @ 00486734 size=98 sig=undefined FUN_00486734() cc=unknown
// callers: FUN_00486798
// callees: FUN_004865e8,FUN_0046ca40,FUN_004866fc

void FUN_00486734(int param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if ((param_1 < 0x20) && (param_2 != 0)) {
    puVar2 = &DAT_0065e02c + param_1 * 7;
    *puVar2 = param_3;
    (&DAT_0065e030)[param_1 * 7] = 1;
    (&DAT_0065e034)[param_1 * 7] = 0;
    (&DAT_0065e038)[param_1 * 7] = 0;
    *(int *)(&DAT_0065e044 + param_1 * 0x1c) = param_2;
    uVar1 = FUN_0046ca40();
    iVar3 = (uVar1 & 7) + 8;
    (&DAT_0065e040)[param_1 * 7] = iVar3;
    (&DAT_0065e03c)[param_1 * 7] = iVar3;
    FUN_004865e8(puVar2);
    FUN_004866fc(puVar2);
  }
  return;
}

