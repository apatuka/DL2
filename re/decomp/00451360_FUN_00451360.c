// FUN_00451360 @ 00451360 size=85 sig=undefined FUN_00451360() cc=unknown
// callers: FUN_00456e44,FUN_00451de4
// callees: 

void FUN_00451360(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  undefined1 *local_8;
  
  iVar1 = param_3 * 3 + -1;
  local_8 = &DAT_0057ce00 + param_2 * 0x24;
  for (iVar4 = param_2; iVar4 < param_2 + iVar1; iVar4 = iVar4 + 1) {
    pbVar3 = local_8 + param_1 + 0x14d;
    for (iVar2 = param_1; iVar2 < iVar1 + param_1; iVar2 = iVar2 + 1) {
      *pbVar3 = *pbVar3 | 3;
      pbVar3 = pbVar3 + 1;
    }
    local_8 = local_8 + 0x24;
  }
  return;
}

