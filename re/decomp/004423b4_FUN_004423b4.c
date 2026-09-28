// FUN_004423b4 @ 004423b4 size=684 sig=undefined FUN_004423b4() cc=unknown
// callers: FUN_00466218,FUN_00461078
// callees: memset

void FUN_004423b4(void)

{
  uint *puVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  ushort *local_24;
  uint *local_20;
  uint *local_14;
  
  memset(&DAT_0055a820,0,0x3440);
  for (puVar5 = &DAT_005a4eac; puVar5 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar5 = puVar5 + 0x2b7) {
    iVar8 = (int)*(char *)((int)puVar5 + 0x22);
    if ((-1 < iVar8) && (iVar8 < 0x20)) {
      (&DAT_0055a822)[iVar8 * 0xd1] = 1;
      switch(*(undefined *)((int)puVar5 + 0x21)) {
      case 0:
        (&DAT_0055a822)[iVar8 * 0xd1] = 0;
        break;
      case 1:
        (&DAT_0055a824)[iVar8 * 0xd1] = (&DAT_0055a824)[iVar8 * 0xd1] | 8;
        break;
      case 2:
        (&DAT_0055a824)[iVar8 * 0xd1] = (&DAT_0055a824)[iVar8 * 0xd1] | 4;
        break;
      case 3:
        (&DAT_0055a824)[iVar8 * 0xd1] = (&DAT_0055a824)[iVar8 * 0xd1] | 1;
        break;
      case 4:
        (&DAT_0055a824)[iVar8 * 0xd1] = (&DAT_0055a824)[iVar8 * 0xd1] | 2;
        break;
      case 5:
        (&DAT_0055a824)[iVar8 * 0xd1] = (&DAT_0055a824)[iVar8 * 0xd1] | 0x16;
      }
      iVar8 = 0;
      local_24 = (ushort *)(puVar5 + 0x224);
      do {
        uVar2 = *local_24;
        for (iVar4 = 0; (uVar2 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
          if (((uVar2 & 1) != 0) &&
             (iVar7 = (iVar8 * 0x10 + iVar4) * 0xadc,
             (&DAT_005a43f2)[iVar7] != *(char *)((int)puVar5 + 0x22))) {
            puVar5[0x228] = puVar5[0x228] | 1 << ((&DAT_005a43f2)[iVar7] & 0x1f);
            puVar1 = (uint *)((int)&DAT_0055a828 + *(char *)((int)puVar5 + 0x22) * 0x1a2);
            *puVar1 = *puVar1 | puVar5[0x228];
          }
          uVar2 = (short)uVar2 >> 1;
        }
        iVar8 = iVar8 + 1;
        local_24 = local_24 + 1;
      } while (iVar8 < 7);
    }
  }
  iVar8 = 0;
  psVar9 = &DAT_0055a822;
  do {
    if ((*psVar9 != 0) && (*(int *)(psVar9 + 3) != 0)) {
      uVar6 = *(uint *)(psVar9 + 3);
      local_20 = &DAT_0055a828;
      for (; uVar6 != 0; uVar6 = (int)uVar6 >> 1) {
        if ((uVar6 & 1) != 0) {
          iVar4 = 0;
          for (uVar3 = *local_20; uVar3 != 0; uVar3 = (int)uVar3 >> 1) {
            if (((uVar3 & 1) != 0) && (iVar8 != iVar4)) {
              *(uint *)(psVar9 + 5) = *(uint *)(psVar9 + 5) | 1 << ((byte)iVar4 & 0x1f);
            }
            iVar4 = iVar4 + 1;
          }
        }
        local_20 = (uint *)((int)local_20 + 0x1a2);
      }
    }
    iVar8 = iVar8 + 1;
    psVar9 = psVar9 + 0xd1;
  } while (iVar8 < 0x20);
  for (puVar5 = &DAT_005a4eac; puVar5 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar5 = puVar5 + 0x2b7) {
    if ((*(char *)((int)puVar5 + 0x21) != '\0') && (puVar5[0x228] != 0)) {
      uVar6 = puVar5[0x228];
      local_14 = &DAT_0055a828;
      for (; uVar6 != 0; uVar6 = (int)uVar6 >> 1) {
        if ((uVar6 & 1) != 0) {
          iVar4 = 0;
          for (uVar3 = *local_14; uVar3 != 0; uVar3 = (int)uVar3 >> 1) {
            if (((uVar3 & 1) != 0) && (iVar8 != iVar4)) {
              puVar5[0x229] = puVar5[0x229] | 1 << ((byte)iVar4 & 0x1f);
            }
            iVar4 = iVar4 + 1;
          }
        }
        local_14 = (uint *)((int)local_14 + 0x1a2);
      }
    }
  }
  return;
}

