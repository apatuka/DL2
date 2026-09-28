// FUN_00447090 @ 00447090 size=197 sig=undefined FUN_00447090() cc=unknown
// callers: FUN_0046e730
// callees: FUN_00446fd4

void FUN_00447090(void)

{
  int iVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    iVar5 = 0;
    puVar2 = (undefined *)((int)puVar3 + 0x6d);
    do {
      *puVar2 = 0xc;
      iVar5 = iVar5 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar5 < 7);
  }
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    if (*(char *)(puVar3 + 8) != -1) {
      iVar5 = 0;
      piVar4 = puVar3 + 0x55;
      do {
        iVar1 = *piVar4;
        if (((iVar1 != 0) && (*(short *)(iVar1 + 0x14) == 0)) &&
           ((*(char *)(iVar1 + 5) == '\f' || (*(char *)(iVar1 + 5) == '\b')))) {
          FUN_00446fd4(puVar3,(int)*(char *)(puVar3 + 8));
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 0xd;
      } while (iVar5 < 0x24);
    }
  }
  for (puVar3 = (undefined4 *)&DAT_00645370; puVar3 < &DAT_00651cb0; puVar3 = puVar3 + 0x17) {
    if (*(char *)((int)puVar3 + 6) == '\x0e') {
      FUN_00446fd4(puVar3[0xf],(int)*(char *)(puVar3 + 2));
    }
  }
  return;
}

