// FUN_00441c90 @ 00441c90 size=205 sig=undefined FUN_00441c90() cc=unknown
// callers: FUN_00427ab0,FUN_00427854
// callees: 

undefined8 FUN_00441c90(void)

{
  undefined2 *puVar1;
  undefined4 *puVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  int local_10;
  
  sVar6 = 0;
  local_10 = 0;
  iVar4 = 0;
  puVar1 = &DAT_0055a830;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[-5] = 0;
    puVar1[2] = 0;
    iVar4 = iVar4 + 1;
    puVar1 = puVar1 + 0xd1;
  } while (iVar4 < 0x20);
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    iVar4 = (int)*(char *)((int)puVar2 + 0x22);
    if (iVar4 < 0x20) {
      if (*(char *)(puVar2 + 8) != -1) {
        (&DAT_0055a830)[iVar4 * 0xd1] = (&DAT_0055a830)[iVar4 * 0xd1] + 1;
      }
      (&DAT_0055a826)[iVar4 * 0xd1] = (&DAT_0055a826)[iVar4 * 0xd1] + 1;
    }
  }
  iVar4 = 0;
  psVar3 = &DAT_0055a826;
  do {
    sVar5 = (short)((int)*psVar3 / (psVar3[5] + 1)) + psVar3[-1];
    psVar3[8] = sVar5;
    if (sVar6 < sVar5) {
      sVar6 = sVar5;
      local_10 = iVar4;
    }
    iVar4 = iVar4 + 1;
    psVar3 = psVar3 + 0xd1;
  } while (iVar4 < 0x20);
  return CONCAT44(local_10,local_10);
}

