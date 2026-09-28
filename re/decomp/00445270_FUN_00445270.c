// FUN_00445270 @ 00445270 size=857 sig=undefined FUN_00445270() cc=unknown
// callers: FUN_00480d78,FUN_0043e058,FUN_00480b80,FUN_0043e0dc,FUN_0048149c
// callees: FUN_00444e70,FUN_00445074,FUN_00444fd4,FUN_004451d4,FUN_0046ca40

void FUN_00445270(int param_1)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  ushort uVar4;
  byte *pbVar5;
  ushort *puVar6;
  ushort *puVar7;
  short *psVar8;
  byte *pbVar9;
  ushort *puVar10;
  ushort uVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  ushort *local_c;
  short local_8;
  short local_6;
  
  pbVar5 = DAT_00561a30;
  while (pbVar9 = pbVar5, pbVar9 != (byte *)0x0) {
    pbVar5 = *(byte **)(pbVar9 + 0x38);
    if ((*pbVar9 & 4) != 0) {
      local_8 = 0;
      iVar14 = param_1;
      while ((0 < iVar14 && (local_8 == 0))) {
        local_c = *(ushort **)(pbVar9 + 0x34);
        if ((local_c != (ushort *)0x0) &&
           (*(short *)(pbVar9 + 0x1e) = *(short *)(pbVar9 + 0x1e) + -1,
           *(short *)(pbVar9 + 0x1e) < 1)) {
          local_6 = 0;
          puVar10 = local_c;
          while ((local_c = puVar10, local_c != (ushort *)0x0 && (local_6 == 0))) {
            uVar11 = *local_c;
            puVar1 = local_c + 1;
            if ((uVar11 & 0x8000) == 0) {
              local_c = puVar1;
              FUN_004451d4(pbVar9,(int)(short)uVar11);
              local_6 = 1;
              puVar10 = local_c;
            }
            else {
              puVar10 = puVar1;
              switch(uVar11 & 0xff) {
              case 1:
                puVar10 = *(ushort **)puVar1;
                break;
              case 2:
                local_c = local_c + 2;
                FUN_00444e70(&local_c,(int)*(short *)(pbVar9 + (short)*puVar1 * 2 + 0x2c));
                puVar10 = local_c;
                break;
              case 3:
                puVar6 = *(ushort **)(local_c + 2);
                puVar10 = local_c + 4;
                if (*(short *)(pbVar9 + (short)*puVar1 * 2 + 0x2c) != 0) {
                  *(short *)(pbVar9 + (short)*puVar1 * 2 + 0x2c) =
                       *(short *)(pbVar9 + (short)*puVar1 * 2 + 0x2c) + -1;
                  puVar10 = puVar6;
                }
                break;
              case 4:
                puVar6 = local_c + 2;
                puVar2 = local_c + 3;
                puVar7 = local_c + 4;
                local_c = local_c + 6;
                puVar7 = *(ushort **)puVar7;
                iVar12 = *(int *)(pbVar9 + 0x16) - *(int *)(pbVar9 + 0x1a);
                if (iVar12 < 0) {
                  iVar12 = iVar12 + 0xf;
                }
                uVar11 = (ushort)(iVar12 >> 4);
                puVar10 = local_c;
                if (uVar11 != *(ushort *)(pbVar9 + (short)*puVar1 * 2 + 0x2c)) {
                  if (*puVar6 == uVar11) {
                    iVar12 = (int)(short)*puVar2;
                  }
                  else {
                    iVar12 = (short)uVar11 + -1;
                  }
                  FUN_004451d4(pbVar9,iVar12);
                  local_6 = 1;
                  puVar10 = puVar7;
                }
                break;
              case 5:
                puVar6 = local_c + 2;
                puVar2 = local_c + 3;
                puVar7 = local_c + 4;
                local_c = local_c + 6;
                puVar7 = *(ushort **)puVar7;
                iVar12 = *(int *)(pbVar9 + 0x16) - *(int *)(pbVar9 + 0x1a);
                if (iVar12 < 0) {
                  iVar12 = iVar12 + 0xf;
                }
                uVar11 = (ushort)(iVar12 >> 4);
                puVar10 = local_c;
                if (uVar11 != *(ushort *)(pbVar9 + (short)*puVar1 * 2 + 0x2c)) {
                  if (uVar11 == *puVar2) {
                    iVar12 = (int)(short)*puVar6;
                  }
                  else {
                    iVar12 = (short)uVar11 + 1;
                  }
                  FUN_004451d4(pbVar9,iVar12);
                  local_6 = 1;
                  puVar10 = puVar7;
                }
                break;
              case 6:
                *(ushort *)(pbVar9 + (short)*puVar1 * 2 + 0x2c) = local_c[2];
                puVar10 = local_c + 3;
                break;
              case 7:
                uVar11 = *puVar1;
                puVar10 = local_c + 3;
                uVar3 = local_c[2];
                local_c = local_c + 4;
                uVar4 = *puVar10;
                uVar13 = FUN_0046ca40();
                *(ushort *)(pbVar9 + (short)uVar11 * 2 + 0x2c) =
                     uVar3 + (short)(uVar13 % (((int)(short)uVar4 - (int)(short)uVar3) + 1U));
                puVar10 = local_c;
                break;
              case 8:
                local_c = puVar1;
                FUN_00445074((int)*(short *)(pbVar9 + 0xe),(int)*(short *)(pbVar9 + 0x10),
                             (int)*(short *)(pbVar9 + 0x12),(int)*(short *)(pbVar9 + 0x14));
                FUN_00444fd4(pbVar9);
                local_6 = 1;
                local_8 = 1;
                puVar10 = local_c;
                break;
              case 9:
                *(ushort *)(pbVar9 + 0x1e) = *puVar1;
                local_6 = 1;
                puVar10 = local_c + 2;
                break;
              case 10:
                puVar10 = local_c + 2;
                if (0 < (short)*puVar1) {
                  *(undefined2 *)(pbVar9 + 0x1e) =
                       *(undefined2 *)(pbVar9 + (short)*puVar1 * 2 + 0x2c);
                  local_6 = 1;
                }
              }
            }
          }
          *(ushort **)(pbVar9 + 0x34) = local_c;
        }
        if (*(short *)(pbVar9 + 0x2a) < 1) {
          if ((*(short *)(pbVar9 + 0x22) != 0) || (*(short *)(pbVar9 + 0x24) != 0)) {
            FUN_00445074((int)*(short *)(pbVar9 + 0xe),(int)*(short *)(pbVar9 + 0x10),
                         (int)*(short *)(pbVar9 + 0x12),(int)*(short *)(pbVar9 + 0x14));
            *(int *)(pbVar9 + 6) = *(int *)(pbVar9 + 6) + (int)*(short *)(pbVar9 + 0x22);
            *(int *)(pbVar9 + 10) = *(int *)(pbVar9 + 10) + (int)*(short *)(pbVar9 + 0x24);
            psVar8 = *(short **)(pbVar9 + 0x16);
            FUN_00445074((*(int *)(pbVar9 + 6) >> 8) + (int)*psVar8,
                         (*(int *)(pbVar9 + 10) >> 8) + (int)psVar8[1],(int)psVar8[2],(int)psVar8[3]
                        );
          }
        }
        else {
          *(short *)(pbVar9 + 0x2a) = *(short *)(pbVar9 + 0x2a) + -1;
        }
        iVar14 = iVar14 + -1;
      }
    }
  }
  return;
}

