// FUN_004513b8 @ 004513b8 size=88 sig=undefined FUN_004513b8() cc=unknown
// callers: FUN_00456e44,FUN_00451de4
// callees: 

void FUN_004513b8(int param_1,int param_2)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int *local_c;
  
  local_c = &DAT_004cfd68;
  iVar4 = 0;
  do {
    iVar3 = 0;
    piVar1 = local_c;
    puVar2 = &DAT_0057ce00 + param_1;
    do {
      if (*piVar1 != 0) {
        puVar2[(param_2 + iVar4) * 0x24 + 0x14d] = puVar2[(param_2 + iVar4) * 0x24 + 0x14d] | 3;
      }
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
      piVar1 = piVar1 + 0xf;
    } while (iVar3 < 0xf);
    iVar4 = iVar4 + 1;
    local_c = local_c + 1;
  } while (iVar4 < 0xf);
  return;
}

