// FUN_00405430 @ 00405430 size=91 sig=undefined FUN_00405430() cc=unknown
// callers: FUN_00473324
// callees: FUN_00403350

void FUN_00405430(void)

{
  int iVar1;
  undefined1 *puVar2;
  char *pcVar3;
  undefined1 *puVar4;
  
  iVar1 = 0;
  puVar2 = &DAT_00522168;
  puVar4 = &DAT_005220a4;
  pcVar3 = &DAT_0059f161;
  do {
    if ('\x02' < *pcVar3) {
      FUN_00403350(iVar1,DAT_0058f1f4);
      *(undefined4 *)(puVar4 + DAT_0058f1f4 * 4) = 0x32;
      *(undefined4 *)(puVar2 + DAT_0058f1f4 * 4) = 0x32;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x1c;
    puVar4 = puVar4 + 0x1c;
    pcVar3 = pcVar3 + 0x2d8;
  } while (iVar1 < 7);
  return;
}

