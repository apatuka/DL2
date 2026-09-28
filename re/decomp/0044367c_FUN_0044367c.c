// FUN_0044367c @ 0044367c size=80 sig=undefined FUN_0044367c() cc=unknown
// callers: FUN_004437c4
// callees: 

void FUN_0044367c(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    iVar3 = 0;
    piVar1 = puVar2 + param_1 * 7 + 0x22d;
    do {
      if (*piVar1 != 0) {
        *piVar1 = *piVar1 + -1;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar3 < 7);
  }
  return;
}

