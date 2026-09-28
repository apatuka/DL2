// FUN_0047c6c0 @ 0047c6c0 size=111 sig=undefined FUN_0047c6c0() cc=unknown
// callers: FUN_0047c730
// callees: 

int FUN_0047c6c0(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = -1;
  iVar2 = 0;
  piVar3 = (int *)(&DAT_004dc438 + param_1 * 0x9c);
  do {
    iVar1 = *piVar3;
    if (((&DAT_005a444e)[iVar1 * 0xadc] != '\0') &&
       ((*(byte *)((int)&DAT_005a43ec + iVar1 * 0xadc + 1) & 1) == 0)) {
      if ((&DAT_005a43f0)[iVar1 * 0xadc] == -1) {
        return iVar1;
      }
      if (iVar2 == 0) {
        iVar4 = iVar1;
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 4);
  if (iVar4 == -1) {
    iVar4 = 0;
  }
  return iVar4;
}

