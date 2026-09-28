// FUN_00466358 @ 00466358 size=96 sig=undefined FUN_00466358() cc=unknown
// callers: FUN_0046686c
// callees: 

int FUN_00466358(int param_1,int param_2,int param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  pcVar1 = (char *)((param_4 * 5 + param_2) * DAT_0058f140 + DAT_0058f134 + param_1 + param_3 * 5);
  iVar4 = 0;
  do {
    iVar3 = 0;
    do {
      if (((int)*pcVar1 & 0xf8U) == 0x40) {
        iVar2 = iVar2 + 1;
      }
      pcVar1 = pcVar1 + 1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
    pcVar1 = pcVar1 + DAT_0058f140 + -5;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  return iVar2;
}

