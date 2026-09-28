// FUN_00442678 @ 00442678 size=125 sig=undefined FUN_00442678() cc=unknown
// callers: FUN_004634a0
// callees: 

void FUN_00442678(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    iVar6 = 0;
    puVar5 = puVar2 + 0x22d;
    puVar4 = puVar2 + 0x25e;
    do {
      if (((*(char *)((int)puVar2 + 0x21) == '\0') && (puVar2[0x22b] == 0)) ||
         (*(char *)((int)puVar2 + 0x21) == '\x05')) {
        *puVar4 = 0;
      }
      else {
        *puVar4 = 0xffffffff;
      }
      iVar3 = 0;
      puVar1 = puVar5;
      do {
        iVar3 = iVar3 + 1;
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
      } while (iVar3 < 7);
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 7;
      puVar4 = puVar4 + 1;
    } while (iVar6 < 7);
  }
  return;
}

