// FUN_00403dbc @ 00403dbc size=113 sig=undefined FUN_00403dbc() cc=unknown
// callers: FUN_00403e30
// callees: FUN_0040e1fc

undefined4 * FUN_00403dbc(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)0x0;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if (*(char *)((int)puVar2 + 0x7e) != '\0') {
      iVar1 = FUN_0040e1fc(param_2,puVar2);
      if (((iVar1 != 0) && (param_1 != puVar2)) &&
         (-1000000 < *(int *)((int)puVar2 + 0xa12) - puVar2[0x296])) {
        puVar3 = puVar2;
      }
    }
  }
  return puVar3;
}

