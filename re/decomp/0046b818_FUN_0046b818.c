// FUN_0046b818 @ 0046b818 size=246 sig=undefined FUN_0046b818() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046b4d0,FUN_0046b3dc,FUN_00423690,FUN_0046f89c

void FUN_0046b818(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_0046f89c();
  iVar3 = 0;
  do {
    iVar2 = FUN_0046b4d0(iVar3);
    if (DAT_0058f17c != 0) {
      FUN_00423690(iVar3,0x99,DAT_0058f17c,DAT_0058f18c,0,0);
    }
    if (DAT_0058f180 != 0) {
      FUN_00423690(iVar3,0x9a,DAT_0058f180,DAT_0058f190,0,0);
    }
    if (DAT_0058f184 != 0) {
      FUN_00423690(iVar3,0x9b,DAT_0058f184,DAT_0058f194,0,0);
    }
    if (DAT_0058f188 != 0) {
      FUN_00423690(iVar3,0x9c,DAT_0058f188,DAT_0058f198,0,0);
    }
    iVar4 = iVar3 * 0x2d8;
    piVar1 = &DAT_0059f16c + iVar3 * 0xb6;
    *piVar1 = *piVar1 - iVar2;
    if (*piVar1 < 0) {
      (&DAT_0059f16c)[iVar3 * 0xb6] = 0;
      if (((&DAT_0059f169)[iVar4] & 1) == 0) {
        FUN_00423690(iVar3,1,0,0,0,0);
        (&DAT_0059f169)[iVar4] = (&DAT_0059f169)[iVar4] | 1;
      }
      else {
        (&DAT_0059f169)[iVar4] = (&DAT_0059f169)[iVar4] | 4;
      }
    }
    else {
      (&DAT_0059f169)[iVar4] = (&DAT_0059f169)[iVar4] & 0xfe;
    }
    if (((&DAT_0059f169)[iVar4] & 4) != 0) {
      FUN_0046b3dc(iVar3);
      (&DAT_0059f169)[iVar4] = (&DAT_0059f169)[iVar4] & 0xfb;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 7);
  return;
}

