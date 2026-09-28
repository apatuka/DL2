// FUN_0046b9a0 @ 0046b9a0 size=69 sig=undefined FUN_0046b9a0() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046b958,FUN_0046b910

void FUN_0046b9a0(void)

{
  short sVar1;
  undefined *puVar2;
  
  for (puVar2 = &DAT_005a43d0; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0xadc) {
    sVar1 = FUN_0046b958(puVar2);
    *(int *)(puVar2 + 0xa82) = (int)sVar1;
    sVar1 = FUN_0046b910(puVar2);
    *(int *)(puVar2 + 0xa86) = (int)sVar1;
  }
  return;
}

