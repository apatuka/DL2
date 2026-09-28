// FUN_0040da78 @ 0040da78 size=124 sig=undefined FUN_0040da78() cc=unknown
// callers: FUN_0040dbc4,FUN_0040c018
// callees: FUN_004726cc,FUN_004013ec

undefined4 * FUN_0040da78(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  iVar3 = -1000000;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if (*(char *)((int)puVar2 + 0x7e) != '\0') {
      iVar1 = FUN_004013ec(param_1,puVar2);
      if (iVar1 != 0) {
        iVar1 = FUN_004726cc(param_2,puVar2,param_1);
        if ((iVar1 < 3) && (iVar1 = *(int *)((int)puVar2 + 0xa0a) - puVar2[0x298], iVar3 < iVar1)) {
          iVar3 = iVar1;
          local_8 = puVar2;
        }
      }
    }
  }
  return local_8;
}

