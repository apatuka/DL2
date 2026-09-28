// FUN_0040edcc @ 0040edcc size=101 sig=undefined FUN_0040edcc() cc=unknown
// callers: FUN_0040ef18
// callees: FUN_0040ecec

undefined4 * FUN_0040edcc(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = -1000000;
  puVar4 = (undefined4 *)0x0;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if (*(char *)((int)puVar2 + 0x7e) != '\0') {
      iVar1 = FUN_0040ecec(puVar2,param_1);
      if ((iVar1 != 0) && (iVar1 = *(int *)((int)puVar2 + 0xa12) - puVar2[0x298], iVar3 < iVar1)) {
        iVar3 = iVar1;
        puVar4 = puVar2;
      }
    }
  }
  return puVar4;
}

