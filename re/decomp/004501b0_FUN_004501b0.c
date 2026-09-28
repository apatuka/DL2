// FUN_004501b0 @ 004501b0 size=83 sig=undefined FUN_004501b0() cc=unknown
// callers: FUN_004618e8
// callees: FUN_0044fe1c,FUN_00450150

void FUN_004501b0(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = FUN_0044fe1c(4);
  if (iVar1 != 0) {
    pcVar3 = &DAT_0059f162;
    for (iVar1 = 0; iVar1 < DAT_004d5aec; iVar1 = iVar1 + 1) {
      iVar2 = FUN_00450150((int)*pcVar3,(int)pcVar3[0x3c]);
      if (iVar2 == 0) {
        DAT_004fc4dc = DAT_004fc4dc & ~(1 << ((byte)iVar1 & 0x1f));
        pcVar3[0x3c] = '\0';
      }
      pcVar3 = pcVar3 + 0x2d8;
    }
  }
  return;
}

