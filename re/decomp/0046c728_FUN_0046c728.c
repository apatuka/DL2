// FUN_0046c728 @ 0046c728 size=85 sig=undefined FUN_0046c728() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046ae1c

void FUN_0046c728(void)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    iVar2 = (int)*(char *)(puVar3 + 8);
    if (iVar2 != -1) {
      sVar1 = FUN_0046ae1c(&DAT_0059f160 + iVar2 * 0x2d8,puVar3);
      (&DAT_0059f16c)[iVar2 * 0xb6] = (&DAT_0059f16c)[iVar2 * 0xb6] + (int)sVar1;
    }
  }
  return;
}

