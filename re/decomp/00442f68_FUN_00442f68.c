// FUN_00442f68 @ 00442f68 size=270 sig=undefined FUN_00442f68() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004412d4,FUN_004012dc

void FUN_00442f68(int param_1)

{
  short *psVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  
  puVar7 = &DAT_005f0410;
  do {
    if ((undefined2 *)0x64536f < puVar7) {
      return;
    }
    if (*(char *)(puVar7 + 2) != '\0') {
      iVar5 = (int)(short)puVar7[4];
      iVar6 = iVar5 * 0xadc;
      if (((char)(&DAT_005a43f0)[iVar6] != -1) && ((uint)(int)(char)(&DAT_005a43f2)[iVar6] < 0x20))
      {
        *(short *)(&DAT_0055a854 +
                  *(char *)((int)puVar7 + 5) * 2 +
                  (char)(&DAT_005a43f2)[iVar6] * 0x1a2 + (char)(&DAT_005a43f0)[iVar6] * 0x2a) =
             *(short *)(&DAT_0055a854 +
                       *(char *)((int)puVar7 + 5) * 2 +
                       (char)(&DAT_005a43f2)[iVar6] * 0x1a2 + (char)(&DAT_005a43f0)[iVar6] * 0x2a) +
             1;
        psVar1 = (short *)(iVar6 + 0x5a4d86 + *(char *)((int)puVar7 + 5) * 2);
        *psVar1 = *psVar1 + 1;
        if (*(char *)((int)puVar7 + 5) == '\x12') {
          cVar2 = (&DAT_005a43f0)[iVar6];
          iVar3 = FUN_004012dc((int)cVar2,*(char *)(puVar7 + 2) + -10,0,0,0,0);
          iVar3 = iVar3 * *(int *)(&DAT_0055f9a0 +
                                  cVar2 * 4 + (short)(&DAT_005a43ea)[iVar5 * 0x56e] * 0x1c);
          (&DAT_0055a804)[(char)(&DAT_005a43f0)[iVar6]] =
               (&DAT_0055a804)[(char)(&DAT_005a43f0)[iVar6]] + iVar3;
          if ((char)(&DAT_005a43f0)[iVar6] != param_1) {
            iVar4 = FUN_004412d4(param_1,(int)(char)(&DAT_005a43f0)[iVar6],2);
            if (iVar4 == 0) {
              *(int *)(&DAT_005a4e20 + iVar6) = *(int *)(&DAT_005a4e20 + iVar6) + iVar3;
              (&DAT_005a4e28)[iVar5 * 0x2b7] = (&DAT_005a4e28)[iVar5 * 0x2b7] + iVar3;
              goto LAB_0044305d;
            }
          }
          *(int *)(&DAT_005a4dda + iVar6) = *(int *)(&DAT_005a4dda + iVar6) + iVar3;
          (&DAT_005a4de2)[iVar5 * 0x2b7] = (&DAT_005a4de2)[iVar5 * 0x2b7] + iVar3;
        }
      }
    }
LAB_0044305d:
    puVar7 = puVar7 + 0x91;
  } while( true );
}

