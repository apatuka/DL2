// FUN_0043cb7c @ 0043cb7c size=107 sig=undefined FUN_0043cb7c() cc=unknown
// callers: CheckTechTree
// callees: FUN_00483f20,FUN_004839bc,FUN_0043c540

void FUN_0043cb7c(void)

{
  int iVar1;
  short *psVar2;
  
  if (DAT_004d5aa0 == '\0') {
    FUN_004839bc(&DAT_00559da8);
  }
  else {
    iVar1 = 1;
    psVar2 = &DAT_004fbbde;
    do {
      if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)*psVar2) != 0) {
        FUN_00483f20(DAT_0058f1f4,&DAT_004fbbac + iVar1 * 0x19);
      }
      iVar1 = iVar1 + 1;
      psVar2 = psVar2 + 0x19;
    } while (iVar1 < 0x30);
  }
  DAT_00559dac = 0;
  FUN_0043c540();
  return;
}

