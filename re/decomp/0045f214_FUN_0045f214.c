// FUN_0045f214 @ 0045f214 size=193 sig=undefined FUN_0045f214() cc=unknown
// callers: RunAITurns
// callees: FUN_0045e6d0

void FUN_0045f214(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  sVar1 = (&DAT_0059f166)[DAT_0058f1f4 * 0x16c];
  if ((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] != DAT_0058f1f4) {
    (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] & 0xfffffffe;
    iVar2 = (int)sVar1;
    if (sVar1 == -1) {
      for (iVar3 = 1; iVar2 = DAT_004c5b50, iVar3 <= DAT_004d5b18; iVar3 = iVar3 + 1) {
        iVar2 = iVar3 * 0xadc;
        if ((((&DAT_005a444e)[iVar2] != '\0') &&
            ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)) &&
           ((char)(&DAT_005a43f0)[iVar2] == DAT_0058f1f4)) {
          iVar2 = (int)(short)(&DAT_005a43ea)[iVar3 * 0x56e];
          break;
        }
      }
    }
    DAT_004c5b50 = iVar2;
    (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] | 1;
  }
  FUN_0045e6d0();
  return;
}

