// FUN_00442c44 @ 00442c44 size=802 sig=undefined FUN_00442c44() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004412d4,FUN_00416ca4,FUN_00401108,FUN_00442900,FUN_00447190,FUN_00446b3c

void FUN_00442c44(int param_1)

{
  int *piVar1;
  short *psVar2;
  char cVar3;
  bool bVar4;
  char cVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  undefined4 *puVar11;
  
  puVar9 = &DAT_00645370;
  do {
    if ((undefined2 *)0x651caf < puVar9) {
      return;
    }
    puVar6 = (undefined4 *)FUN_00442900(puVar9,param_1);
    if (puVar6 != (undefined4 *)0x0) {
      iVar8 = *(char *)((int)puVar6 + 0x22) * 0x1a2;
      iVar10 = (int)*(short *)((int)puVar6 + 0x1a);
      iVar7 = FUN_00401108(puVar9,1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                                  *(uint *)(&DAT_0055eba0 + iVar10 * 4),
                           1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                           *(uint *)(&DAT_0055ef20 + iVar10 * 4),
                           1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                           *(uint *)(&DAT_0055f2a0 + iVar10 * 4),
                           1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                           *(uint *)(&DAT_0055f620 + iVar10 * 4));
      iVar7 = iVar7 * *(int *)(&DAT_0055f9a0 + *(char *)(puVar9 + 4) * 4 + iVar10 * 0x1c);
      cVar5 = *(char *)(puVar9 + 4);
      (&DAT_0055a804)[cVar5] = (&DAT_0055a804)[cVar5] + iVar7;
      cVar3 = (&DAT_004faf8d)[*(char *)(puVar9 + 3) * 0x24];
      bVar4 = (cVar3 == '\x01' || cVar3 == '\x02') || cVar3 == '\x06';
      if (bVar4) {
        piVar1 = (int *)((int)&DAT_0055a97a + cVar5 * 4 + iVar8);
        *piVar1 = *piVar1 + iVar7;
      }
      piVar1 = (int *)((int)&DAT_0055a996 + *(char *)(puVar9 + 4) * 4 + iVar8);
      *piVar1 = *piVar1 + iVar7;
      if ((&DAT_004faf87)[*(char *)(puVar9 + 3) * 0x24] != '\t') {
        if (*(char *)(puVar9 + 4) != param_1) {
          iVar8 = FUN_004412d4(param_1,(int)*(char *)(puVar9 + 4),2);
          if (iVar8 == 0) {
            puVar6[0x296] = puVar6[0x296] + iVar7;
            psVar2 = (short *)((int)puVar6 + *(char *)((int)puVar9 + 7) * 2 + 0xa26);
            *psVar2 = *psVar2 + 1;
            if (bVar4) {
              puVar6[0x295] = puVar6[0x295] + iVar7;
            }
            goto LAB_00442dea;
          }
        }
        *(int *)((int)puVar6 + 0xa12) = *(int *)((int)puVar6 + 0xa12) + iVar7;
        psVar2 = (short *)((int)puVar6 + *(char *)((int)puVar9 + 7) * 2 + 0x9e0);
        *psVar2 = *psVar2 + 1;
        if (bVar4) {
          *(int *)((int)puVar6 + 0xa0e) = *(int *)((int)puVar6 + 0xa0e) + iVar7;
        }
      }
LAB_00442dea:
      iVar8 = FUN_00416ca4(puVar9);
      if ((iVar8 != 0) || (*(char *)(puVar9 + 3) == '\x1e')) {
        puVar6[param_1 * 7 + *(char *)(puVar9 + 4) + 0x22d] = 10;
      }
      iVar10 = 0x2000 << (*(byte *)(puVar9 + 4) & 0x1f);
      iVar8 = (int)*(char *)(puVar9 + 4);
      iVar7 = (int)(char)(&DAT_004faf8d)[*(char *)(puVar9 + 3) * 0x24];
      cVar5 = FUN_00447190(puVar9);
      FUN_00446b3c(*(undefined4 *)(puVar9 + 0x1c),(int)cVar5,iVar7,iVar8,iVar10);
      for (puVar11 = &DAT_005a4eac; puVar11 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
          puVar11 = puVar11 + 0x2b7) {
        if (((0x2000 << (*(byte *)(puVar9 + 4) & 0x1f) & puVar11[7]) != 0) && (puVar11 != puVar6)) {
          iVar7 = (int)*(short *)((int)puVar11 + 0x1a);
          iVar8 = FUN_00401108(puVar9,1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                                      *(uint *)(&DAT_0055ed60 + iVar7 * 4),
                               1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                               *(uint *)(&DAT_0055f0e0 + iVar7 * 4),
                               1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                               *(uint *)(&DAT_0055f460 + iVar7 * 4),
                               1 << (*(byte *)(puVar9 + 4) & 0x1f) &
                               *(uint *)(&DAT_0055f7e0 + iVar7 * 4));
          iVar8 = iVar8 * *(int *)(&DAT_005605e0 + *(char *)(puVar9 + 4) * 4 + iVar7 * 0x1c);
          if (*(char *)(puVar9 + 4) != param_1) {
            iVar7 = FUN_004412d4(param_1,(int)*(char *)(puVar9 + 4),2);
            if (iVar7 == 0) {
              puVar11[0x298] = puVar11[0x298] + iVar8;
              if (bVar4) {
                puVar11[0x297] = puVar11[0x297] + iVar8;
              }
              goto LAB_00442f2d;
            }
          }
          *(int *)((int)puVar11 + 0xa1a) = *(int *)((int)puVar11 + 0xa1a) + iVar8;
          if (bVar4) {
            *(int *)((int)puVar11 + 0xa16) = *(int *)((int)puVar11 + 0xa16) + iVar8;
          }
        }
LAB_00442f2d:
      }
    }
    puVar9 = puVar9 + 0x2e;
  } while( true );
}

