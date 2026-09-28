// FUN_0047bf78 @ 0047bf78 size=100 sig=undefined FUN_0047bf78() cc=unknown
// callers: FUN_0047c53c
// callees: 

void FUN_0047bf78(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *local_c;
  int local_8;
  
  local_8 = 0;
  local_c = &DAT_004fbbac;
  do {
    *local_c = *param_1;
    local_c[1] = param_1[1];
    iVar2 = 0;
    puVar3 = local_c + 3;
    puVar1 = param_1 + 2;
    do {
      *puVar3 = *puVar1;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 < 7);
    local_8 = local_8 + 1;
    local_c = local_c + 0x19;
    param_1 = param_1 + 9;
  } while (local_8 < 0x30);
  return;
}

