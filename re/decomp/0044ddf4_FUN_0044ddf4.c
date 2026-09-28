// FUN_0044ddf4 @ 0044ddf4 size=84 sig=undefined FUN_0044ddf4() cc=unknown
// callers: FUN_0044e0a8,FUN_00445f08,FUN_0041d414,ProduceUnits,FUN_0046b3dc,FUN_0041026c,FUN_0041ffd4,FUN_00401fbc,FUN_004383a4,FUN_0041c418,FUN_0044df94,WriteUnitData,FUN_00431734,FUN_00420e34
// callees: 

void FUN_0044ddf4(undefined4 param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  *param_3 = (int)*(short *)(&DAT_004faf88 + param_2 * 0x24);
  iVar2 = 0;
  piVar1 = (int *)(&DAT_004fb4f8 + param_2 * 0x2c);
  piVar3 = param_3;
  do {
    piVar3 = piVar3 + 1;
    *piVar3 = *piVar1;
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0xb);
  param_3[0xc] = (int)(char)(&DAT_004faf8b)[param_2 * 0x24];
  return;
}

