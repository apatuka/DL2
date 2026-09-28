// CreateRandomEvents @ 0047d71c size=134 sig=undefined CreateRandomEvents() cc=unknown
// callers: WinMain
// callees: FUN_0047d49c,FUN_0047cad4,FUN_0046c9d8,WaitSync
// strings: \"CreateRandomEvents1\"|\"CreateRnd\"|\"CreateRnd2\"|\"CreateRandomEvents2\"

/* Random events per turn (plague, flood, earthquake...) */

void CreateRandomEvents(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  WaitSync(s_CreateRandomEvents1_004dcb8a);
  FUN_0047d49c();
  if ((8 < DAT_0059f154) && (DAT_004d5b04 != 0)) {
    if (DAT_00654804 == 0) {
      uVar2 = FUN_0046c9d8(100,s_CreateRnd_004dcb9e);
      if (uVar2 < 100) {
        iVar3 = FUN_0046c9d8(9,s_CreateRnd2_004dcba8);
        FUN_0047cad4(iVar3 + 1);
      }
    }
    iVar3 = 0;
    do {
      iVar1 = (&DAT_00654804)[iVar3 * 7];
      if (iVar1 != 0) {
        (*(code *)(&PTR_FUN_004dcab0)[iVar1])(&DAT_00654804 + iVar3 * 7);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
  }
  WaitSync(s_CreateRandomEvents2_004dcbb3);
  return;
}

