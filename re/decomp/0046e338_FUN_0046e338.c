// FUN_0046e338 @ 0046e338 size=58 sig=undefined FUN_0046e338() cc=unknown
// callers: FUN_004732d0,FUN_0047d2f0,ResetNetGame,FUN_0046e730,FUN_00458b54,WinMain
// callees: FUN_0046e064

void FUN_0046e338(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  
  for (iVar3 = 0; iVar3 <= DAT_004d5b18; iVar3 = iVar3 + 1) {
    iVar2 = 0;
    puVar4 = &DAT_005a4436 + iVar3 * 0xadc;
    do {
      uVar1 = FUN_0046e064(&DAT_005a43d0 + iVar3 * 0xadc,iVar2);
      *puVar4 = uVar1;
      iVar2 = iVar2 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar2 < 7);
  }
  return;
}

