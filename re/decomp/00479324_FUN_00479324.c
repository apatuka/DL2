// FUN_00479324 @ 00479324 size=614 sig=undefined FUN_00479324() cc=unknown
// callers: ResetNetGame
// callees: memset,memcpy

void FUN_00479324(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  undefined2 *puVar5;
  char *pcVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  int iVar10;
  ushort *puVar11;
  ushort *puVar12;
  undefined4 *puVar13;
  uint uVar14;
  int *local_4c;
  undefined4 *local_48;
  undefined4 *local_40;
  int local_3c [7];
  ushort local_20 [8];
  
  memset(local_3c,0xff,0x1c);
  iVar4 = 0;
  pcVar6 = &DAT_0059f161;
  do {
    if (*pcVar6 != '\0') {
      iVar10 = 0;
      piVar9 = local_3c;
      piVar7 = &DAT_0065361c;
      do {
        if ((int)pcVar6[1] == *piVar7) {
          *piVar9 = iVar4;
          break;
        }
        iVar10 = iVar10 + 1;
        piVar9 = piVar9 + 1;
        piVar7 = piVar7 + 1;
      } while (iVar10 < 7);
    }
    iVar4 = iVar4 + 1;
    pcVar6 = pcVar6 + 0x2d8;
    if (6 < iVar4) {
      for (puVar8 = &DAT_005a4eac; puVar8 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar8 = puVar8 + 0x2b7) {
        if ((*(char *)((int)puVar8 + 0x7e) != '\0') && (*(char *)(puVar8 + 8) != -1)) {
          *(char *)(puVar8 + 8) = (char)local_3c[*(char *)(puVar8 + 8)];
        }
        if (puVar8[0x22a] != 0) {
          uVar14 = 0;
          iVar4 = 0;
          piVar9 = local_3c;
          do {
            if ((1 << ((byte)iVar4 & 0x1f) & puVar8[0x22a]) != 0) {
              uVar14 = uVar14 | 1 << ((byte)*piVar9 & 0x1f);
            }
            iVar4 = iVar4 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar4 < 7);
          puVar8[0x22a] = uVar14;
        }
      }
      for (puVar5 = &DAT_00645370; puVar5 < (undefined2 *)0x651cb1; puVar5 = puVar5 + 0x2e) {
        if (*(char *)(puVar5 + 3) != '\0') {
          *(char *)(puVar5 + 4) = (char)local_3c[*(char *)(puVar5 + 4)];
        }
      }
      for (puVar11 = &DAT_004fbbac; puVar11 < (ushort *)((int)&DAT_004fc50c + 1);
          puVar11 = puVar11 + 0x19) {
        uVar1 = *puVar11;
        uVar2 = puVar11[1];
        memcpy(local_20,puVar11 + 3,0xe);
        *puVar11 = 0;
        puVar11[1] = 0;
        puVar12 = local_20;
        piVar9 = local_3c;
        iVar4 = 0;
        do {
          uVar14 = 1 << ((byte)iVar4 & 0x1f);
          if ((uVar14 & (int)(short)uVar1) != 0) {
            *puVar11 = *puVar11 | 1 << ((byte)*piVar9 & 0x1f);
          }
          if ((uVar14 & (int)(short)uVar2) != 0) {
            puVar11[1] = puVar11[1] | 1 << ((byte)*piVar9 & 0x1f);
          }
          uVar3 = *puVar12;
          iVar10 = *piVar9;
          piVar9 = piVar9 + 1;
          puVar12 = puVar12 + 1;
          puVar11[iVar10 + 3] = uVar3;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 7);
      }
      iVar4 = 0;
      puVar13 = &DAT_0065405c;
      puVar8 = &DAT_00654120;
      local_4c = local_3c;
      do {
        if (*local_4c != -1) {
          iVar10 = 0;
          piVar9 = local_3c;
          local_48 = puVar13;
          local_40 = puVar8;
          do {
            if (*piVar9 != -1) {
              (&DAT_0059f3da)[*local_4c * 0xb6 + *piVar9] = *local_48;
              (&DAT_0059f3f6)[*local_4c * 0xb6 + *piVar9] = *local_40;
            }
            local_40 = local_40 + 1;
            local_48 = local_48 + 1;
            iVar10 = iVar10 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar10 < 7);
        }
        iVar4 = iVar4 + 1;
        puVar13 = puVar13 + 7;
        puVar8 = puVar8 + 7;
        local_4c = local_4c + 1;
      } while (iVar4 < 7);
      memset(&DAT_0065e42c,0,0xe);
      memset(&DAT_0065e43a,0,0xe);
      return;
    }
  } while( true );
}

