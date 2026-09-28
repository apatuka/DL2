// FUN_0047c730 @ 0047c730 size=872 sig=undefined FUN_0047c730() cc=unknown
// callers: WinMain
// callees: memset,FUN_00441700,FUN_00404f5c,FUN_0044bea8,FUN_0047c6c0,FUN_0044a000,SyncCreateBuilding,SyncCreateUnit,FUN_00423690,FUN_00483d58,FUN_00441128,FUN_0044fdf0,FUN_0044fe1c,FUN_00401830

void FUN_0047c730(void)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  byte bVar5;
  char *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  undefined *puVar13;
  int local_24;
  int local_1c;
  int local_18;
  short *local_14;
  
  iVar2 = FUN_0044fe1c(6);
  if (iVar2 != 0) {
    iVar2 = FUN_0044fdf0(6);
    iVar2 = iVar2 * 0x44 + DAT_004d5a94 * 0xd8;
    bVar1 = false;
    piVar10 = (int *)(&DAT_004c61ac + iVar2);
    for (iVar7 = 1; iVar7 <= *(int *)(&DAT_004c61a4 + iVar2); iVar7 = iVar7 + 1) {
      if (*piVar10 + -1 == DAT_0059f154) {
        bVar1 = true;
        local_24 = piVar10[-1];
      }
      piVar10 = piVar10 + 2;
    }
    if (bVar1) {
      iVar7 = FUN_0047c6c0(local_24);
      iVar2 = DAT_004d5aec;
      iVar12 = iVar7 * 0xadc;
      puVar13 = &DAT_005a43d0 + iVar12;
      DAT_004d5aec = DAT_004d5aec + 1;
      iVar11 = 0;
      puVar3 = (undefined4 *)(&DAT_004dc44c + local_24 * 0x9c);
      (&DAT_0059f162)[iVar2 * 0x2d8] = (&DAT_004dc434)[local_24 * 0x9c];
      (&DAT_0059f161)[iVar2 * 0x2d8] = 3;
      bVar5 = (byte)iVar2;
      (&DAT_0059f160)[iVar2 * 0x2d8] = bVar5;
      (&DAT_0059f198)[iVar2 * 0x2d8] = 0x7f;
      (&DAT_0059f16c)[iVar2 * 0xb6] = *puVar3;
      (&DAT_0059f19e)[iVar2 * 0x2d8] = 0;
      (&DAT_0059f16b)[iVar2 * 0x2d8] = 2;
      (&DAT_005a0548)[iVar2] = (undefined1)DAT_004d5b0c;
      DAT_0059f0fc = DAT_0059f0fc | '\x01' << (bVar5 & 0x1f);
      local_14 = &DAT_004fbbcc;
      do {
        if ((int)*local_14 <= *(int *)(&DAT_004dc448 + local_24 * 0x9c)) {
          FUN_00483d58(iVar2,&DAT_004fbbac + iVar11 * 0x19);
        }
        iVar11 = iVar11 + 1;
        local_14 = local_14 + 0x19;
      } while (iVar11 < 0x30);
      (&DAT_0059f19a)[iVar2 * 0xb6] = 0;
      memset(&DAT_0059f3da + iVar2 * 0xb6,0,0x1c);
      puVar8 = &DAT_0052245c + iVar2 * 7;
      for (iVar11 = 0; iVar11 < DAT_004d5aec; iVar11 = iVar11 + 1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      local_1c = 0;
      piVar10 = (int *)(&DAT_004dc4cc + local_24 * 0x9c);
      do {
        if (*piVar10 != 0) {
          iVar11 = 0;
          pcVar6 = &DAT_0059f162;
          do {
            if ((int)*pcVar6 == piVar10[-1]) {
              FUN_00441700(iVar2,iVar11,*piVar10);
              break;
            }
            iVar11 = iVar11 + 1;
            pcVar6 = pcVar6 + 0x2d8;
          } while (iVar11 < 7);
        }
        local_1c = local_1c + 1;
        piVar10 = piVar10 + 2;
      } while (local_1c < 1);
      FUN_00441128();
      iVar11 = 1;
      (&DAT_0059f166)[iVar2 * 0x16c] = (&DAT_005a43ea)[iVar7 * 0x56e];
      local_14 = (short *)(&DAT_005a440e + iVar7 * 0x2b7);
      do {
        puVar3 = puVar3 + 1;
        iVar11 = iVar11 + 1;
        *(undefined4 *)local_14 = *puVar3;
        local_14 = (short *)((int)local_14 + 4);
      } while (iVar11 < 0xb);
      if ((&DAT_005a43f0)[iVar12] == -1) {
        *(undefined2 *)(&DAT_005a4d82 + iVar12) = 0;
        (&DAT_005a43f0)[iVar12] = bVar5;
        (&DAT_005a4405)[iVar12] = 100;
        if ((&DAT_005a43f1)[iVar12] == '\0') {
          SyncCreateBuilding(puVar13,0x26);
        }
        else {
          SyncCreateBuilding(puVar13,3);
          SyncCreateBuilding(puVar13,0x25);
        }
      }
      iVar11 = 0;
      do {
        iVar9 = local_24 * 0x9c + iVar11 * 8;
        piVar10 = (int *)(&DAT_004dc478 + iVar9);
        if (*piVar10 != 0) {
          for (local_18 = 0; local_18 < *(int *)(&DAT_004dc47c + iVar9); local_18 = local_18 + 1) {
            if ((*piVar10 == 0x19) && (iVar2 == (char)(&DAT_005a43f0)[iVar12])) {
              (&DAT_005a4400)[iVar7 * 0x56e] = (&DAT_005a4400)[iVar7 * 0x56e] + 100;
              *(short *)(&DAT_005a4408 + iVar12) = *(short *)(&DAT_005a4408 + iVar12) + 100;
            }
            else {
              iVar4 = SyncCreateUnit(puVar13,iVar2,*piVar10);
              if (iVar4 != 0) {
                *(undefined2 *)(iVar4 + 0x28) = 200;
              }
            }
          }
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 10);
      FUN_00401830(iVar2);
      FUN_00404f5c(iVar2);
      FUN_0044bea8(puVar13);
      FUN_0044a000();
      FUN_00423690(DAT_0058f1f4,0x93,(&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[iVar2 * 0x2d8]],
                   puVar13,0,0);
    }
  }
  return;
}

