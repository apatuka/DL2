// InitHelp @ 00425690 size=91 sig=undefined InitHelp() cc=unknown
// callers: WinMain
// callees: 

/* Initializes context help */

void InitHelp(void)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < DAT_004d4d82; iVar2 = iVar2 + 1) {
    *(short *)(PTR_DAT_004d4d7a + iVar2 * 0x24 + 0x20) = (short)iVar2;
    for (iVar1 = 0; iVar1 < *(short *)(PTR_DAT_004d4d7a + iVar2 * 0x24 + 0x1e); iVar1 = iVar1 + 1) {
      *(short *)(*(int *)(PTR_DAT_004d4d7a + iVar2 * 0x24 + 0x16) + 0x20 + iVar1 * 0x24) =
           (short)iVar1;
    }
  }
  DAT_00557564 = DAT_0051dc18;
  DAT_0051dc18 = 0xc;
  return;
}

