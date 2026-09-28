// FUN_0047b834 @ 0047b834 size=128 sig=undefined FUN_0047b834() cc=unknown
// callers: FUN_0047b4ac
// callees: FUN_0047b660

void FUN_0047b834(undefined4 param_1)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined2 local_36c [432];
  undefined2 *local_c;
  int local_8;
  
  local_c = local_36c;
  local_8 = 0;
  puVar4 = &DAT_004fbbac;
  do {
    *local_c = *puVar4;
    local_c[1] = puVar4[1];
    iVar2 = 0;
    puVar3 = local_c + 2;
    puVar1 = puVar4 + 3;
    do {
      *puVar3 = *puVar1;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 < 7);
    local_8 = local_8 + 1;
    local_c = local_c + 9;
    puVar4 = puVar4 + 0x19;
  } while (local_8 < 0x30);
  FUN_0047b660(param_1,2,local_36c,0x360);
  return;
}

