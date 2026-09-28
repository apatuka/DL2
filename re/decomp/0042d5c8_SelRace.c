// SelRace @ 0042d5c8 size=152 sig=undefined SelRace() cc=unknown
// callers: FUN_0042dbb8,FUN_0042da3c
// callees: FUN_0046c9d8,FUN_0046ca40
// strings: \"SelRace\"

/* auto-named from string evidence: SelRace */

void SelRace(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  if (DAT_00557c7c == DAT_0058f1f4) {
    uVar2 = FUN_0046ca40();
    uVar2 = uVar2 % 7;
  }
  else {
    uVar2 = FUN_0046c9d8(7,s_SelRace_004c3688);
  }
  do {
    while ((bVar1 = true, DAT_004d513c != 0 &&
           ((1 << ((byte)uVar2 & 0x1f) & (int)DAT_0058f12e) == 0))) {
      uVar2 = uVar2 + 1;
      if (6 < (int)uVar2) {
        uVar2 = 0;
      }
    }
    pcVar4 = &DAT_0059f162;
    for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
      if (uVar2 == (int)*pcVar4) {
        uVar2 = uVar2 + 1;
        if (6 < (int)uVar2) {
          uVar2 = 0;
        }
        bVar1 = false;
        break;
      }
      pcVar4 = pcVar4 + 0x2d8;
    }
    if (bVar1) {
      return;
    }
  } while( true );
}

