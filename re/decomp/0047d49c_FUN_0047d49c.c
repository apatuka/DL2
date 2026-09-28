// FUN_0047d49c @ 0047d49c size=640 sig=undefined FUN_0047d49c() cc=unknown
// callers: CreateRandomEvents
// callees: FUN_0044bea8,FUN_0046c9d8,FUN_0047d460,FUN_00423690,DoRiot
// strings: \"Scandal\"|\"Scandal2\"|\"Scandal3\"|\"Scandal4\"|\"Scandal5\"

void FUN_0047d49c(void)

{
  short sVar1;
  short sVar2;
  bool bVar3;
  char cVar4;
  uint uVar5;
  int *piVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int local_38;
  int local_30;
  int local_28 [2];
  int local_20 [3];
  int local_14;
  
  local_38 = 0;
  do {
    bVar3 = false;
    local_30 = 0;
    iVar9 = 0;
    do {
      iVar8 = local_38 * 200 + iVar9 * 8;
      sVar1 = (&DAT_00654ac0)[iVar9 * 4 + local_38 * 100];
      if (sVar1 != -1) {
        iVar10 = sVar1 * 0x2d8;
        uVar11 = ((int)*(short *)(&DAT_004dca60 + *(short *)(&DAT_00654ac4 + iVar8) * 2) *
                 (int)*(short *)(&DAT_0055a0ca + (char)(&DAT_0059f162)[iVar10] * 2)) / 100 +
                 (int)*(short *)(&DAT_00654ac6 + iVar8) / 0x14;
        if ('\x02' < (char)(&DAT_0059f161)[iVar10]) {
          uVar11 = uVar11 / 2;
        }
        sVar1 = *(short *)(&DAT_00654ac2 + iVar8);
        if ((0 < sVar1) && (sVar1 <= DAT_004d5b18)) {
          iVar8 = sVar1 * 0xadc;
          puVar7 = &DAT_005a43d0 + iVar8;
          if (!bVar3) {
            bVar3 = true;
            (&DAT_0059f16a)[iVar10] = (&DAT_0059f16a)[iVar10] + '\x01';
          }
          uVar5 = FUN_0046c9d8(100,s_Scandal_004dcb5e);
          if (uVar5 < uVar11) {
            local_28[0] = (int)(char)(&DAT_0059f16a)[iVar10];
            local_28[1] = 0xb;
            if ((char)(&DAT_0059f16a)[iVar10] < 0xc) {
              piVar6 = local_28;
            }
            else {
              piVar6 = local_28 + 1;
            }
            iVar10 = *piVar6;
            sVar2 = *(short *)(&DAT_004dca6c + iVar10 * 6);
            local_30 = local_30 + *(short *)(&DAT_004dca6a + iVar10 * 6);
            local_20[0] = (int)*(short *)(&DAT_004dca68 + iVar10 * 6) -
                          (int)*(short *)(&DAT_004dca6a + iVar10 * 6);
            local_20[1] = 0;
            if (local_20[0] < 0) {
              piVar6 = local_20 + 1;
            }
            else {
              piVar6 = local_20;
            }
            local_20[0] = *piVar6;
            cVar4 = FUN_0046c9d8(local_20[0],s_Scandal2_004dcb66);
            (&DAT_005a43f7)[iVar8] = (&DAT_005a43f7)[iVar8] - (cVar4 + (char)local_20[0]);
            FUN_00423690((int)(short)(&DAT_00654ac0)[iVar9 * 4 + local_38 * 100],0x5c,puVar7,0,0,0);
            uVar11 = FUN_0046c9d8(100,s_Scandal3_004dcb6f);
            if (uVar11 < (uint)(int)sVar2) {
              uVar11 = FUN_0046c9d8((short)(&DAT_005a4400)[sVar1 * 0x56e] + 3,s_Scandal4_004dcb78);
              FUN_00423690((int)(char)(&DAT_005a43f0)[iVar8],0x54,puVar7,uVar11 >> 2,0,0);
              DoRiot(puVar7,uVar11 >> 2);
            }
          }
        }
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < 0x19);
    if (local_30 != 0) {
      for (iVar9 = 0; iVar9 <= DAT_004d5b18; iVar9 = iVar9 + 1) {
        iVar8 = iVar9 * 0xadc;
        if ((char)(&DAT_005a43f0)[iVar8] == local_38) {
          cVar4 = FUN_0046c9d8(local_30,s_Scandal5_004dcb81);
          (&DAT_005a43f7)[iVar8] = (&DAT_005a43f7)[iVar8] - (cVar4 + (char)local_30);
          local_20[2] = (int)(char)(&DAT_005a43f7)[iVar8];
          local_14 = 0;
          if ((char)(&DAT_005a43f7)[iVar8] < 0) {
            piVar6 = &local_14;
          }
          else {
            piVar6 = local_20 + 2;
          }
          (&DAT_005a43f7)[iVar8] = (char)*piVar6;
          FUN_0044bea8(&DAT_005a43d0 + iVar8);
        }
      }
    }
    local_38 = local_38 + 1;
  } while (local_38 < 7);
  FUN_0047d460();
  return;
}

