// FUN_0046c780 @ 0046c780 size=81 sig=undefined FUN_0046c780() cc=unknown
// callers: FUN_0046c7d4,FUN_0046e730,WinMain
// callees: FUN_0044bea8,FUN_0046c1f0

void FUN_0046c780(void)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  FUN_0046c1f0();
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    FUN_0044bea8(puVar3);
    iVar2 = 1;
    piVar1 = (int *)((int)puVar3 + 0x3e);
    do {
      if (10000 < *piVar1) {
        *piVar1 = 10000;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 0xb);
  }
  return;
}

