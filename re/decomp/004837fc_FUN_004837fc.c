// FUN_004837fc @ 004837fc size=160 sig=undefined FUN_004837fc() cc=unknown
// callers: FUN_0046e730
// callees: 

void FUN_004837fc(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  
  iVar4 = 0;
  pcVar5 = &DAT_0059f161;
  do {
    if ((*pcVar5 != '\0') && ((1 << ((byte)iVar4 & 0x1f) & (int)DAT_004fc4da) != 0)) {
      for (iVar1 = 1; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
        iVar2 = iVar1 * 0xadc;
        if (((((&DAT_005a444e)[iVar2] != '\0') && ((&DAT_005a4400)[iVar1 * 0x56e] != 0)) &&
            ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)) &&
           (iVar4 == (char)(&DAT_005a43f0)[iVar2])) {
          iVar2 = 1;
          piVar3 = &DAT_005a440e + iVar1 * 0x2b7;
          do {
            if (((iVar2 != 3) && (iVar2 != 5)) && ((iVar2 != 6 && (iVar2 != 7)))) {
              *piVar3 = *piVar3 + 100;
            }
            iVar2 = iVar2 + 1;
            piVar3 = piVar3 + 1;
          } while (iVar2 < 10);
        }
      }
      *(int *)(pcVar5 + 0xb) = *(int *)(pcVar5 + 0xb) + 0xfa;
    }
    iVar4 = iVar4 + 1;
    pcVar5 = pcVar5 + 0x2d8;
  } while (iVar4 < 7);
  return;
}

