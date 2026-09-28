// FUN_004663b8 @ 004663b8 size=169 sig=undefined FUN_004663b8() cc=unknown
// callers: FUN_004669d8
// callees: 

void FUN_004663b8(int param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  
  pcVar3 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
  cVar1 = *pcVar3;
  cVar2 = pcVar3[1];
  iVar7 = 0;
  do {
    pbVar5 = (byte *)(((short)(iVar7 / 6) * 5 + cVar2 * 0x20) * DAT_0058f140 + DAT_0058f134 +
                      cVar1 * 0x20 + (short)(iVar7 % 6) * 5);
    iVar4 = 0;
    do {
      iVar6 = 0;
      do {
        if (((int)(char)*pbVar5 & 0xf8U) == 0x40) {
          *pbVar5 = *pbVar5 & 7;
          *pbVar5 = *pbVar5 | 0x30;
        }
        pbVar5 = pbVar5 + 1;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 5);
      pbVar5 = pbVar5 + DAT_0058f140 + -5;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 5);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x24);
  return;
}

