// FUN_0046c1f0 @ 0046c1f0 size=100 sig=undefined FUN_0046c1f0() cc=unknown
// callers: FUN_00473e9c,FUN_0046c780,FUN_00414004
// callees: GetBuildingTasks

void FUN_0046c1f0(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  for (iVar2 = 0; iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    if ((&DAT_005a43f0)[iVar2 * 0xadc] != -1) {
      iVar3 = 0;
      piVar1 = &DAT_005a4524 + iVar2 * 0x2b7;
      do {
        if (*piVar1 != 0) {
          GetBuildingTasks(&DAT_0059f160 + (char)(&DAT_005a43f0)[iVar2 * 0xadc] * 0x2d8,*piVar1);
        }
        iVar3 = iVar3 + 1;
        piVar1 = piVar1 + 0xd;
      } while (iVar3 < 0x24);
    }
  }
  return;
}

