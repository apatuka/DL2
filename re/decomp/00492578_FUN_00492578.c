// FUN_00492578 @ 00492578 size=1332 sig=undefined FUN_00492578() cc=unknown
// callers: FUN_0048468c,FUN_00492d67,FUN_0049f9c0,FUN_00492aee,FUN_00492ac4
// callees: FUN_00492083,FUN_0048f774,FUN_00499840

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00492578(undefined4 param_1)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  short sVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  int iVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined1 *puVar15;
  uint local_48;
  int local_44;
  int local_40;
  int local_38;
  int local_34;
  int local_2c;
  int local_28;
  int local_24;
  uint local_1c;
  byte *local_10;
  byte *local_c;
  
  if (DAT_0065ebf8 != 0) {
    sVar4 = FUN_00492083(param_1);
    iVar10 = DAT_0065ec4c;
    uVar1 = *(ushort *)(DAT_0065ec4c + DAT_0065ec38 + (short)(sVar4 - DAT_0065ec20) * 2);
    sVar4 = sVar4 - DAT_0065ec20;
    if (uVar1 == 0xffff) {
      uVar1 = *(ushort *)(DAT_0065ec4c + DAT_0065ec38 + DAT_0065ec70 * 2);
      sVar4 = DAT_0065ec70;
    }
    local_1c = (uint)uVar1;
    if (sVar4 == 0x20) {
      local_40 = 0;
    }
    else {
      local_40 = (char)(uVar1 >> 8) + DAT_0065ec24;
    }
    local_1c = local_1c & 0xff;
    local_24 = DAT_0065ec40 + local_40;
    local_2c = local_1c + DAT_0065ec40;
    if (DAT_0065ec40 < local_24) {
      local_24 = DAT_0065ec40;
    }
    iVar5 = DAT_0065ec3c - DAT_0065ebfc;
    local_28 = DAT_0065ec3c + DAT_0065ec00;
    iVar7 = DAT_0065ec28;
    if (sVar4 == 0x20) {
      iVar7 = DAT_0065ec2c;
    }
    DAT_0065ec40 = iVar7 + local_2c;
    local_44 = DAT_0065ec0c;
    local_48 = local_1c;
    if (((byte)DAT_0065ec54 & 1) != 0) {
      local_2c = local_2c + DAT_0065ec58;
      local_28 = local_28 + DAT_0065ec5c;
      local_48 = local_1c + DAT_0065ec58;
      local_44 = DAT_0065ec0c + DAT_0065ec5c;
    }
    if ((((iVar5 < DAT_0065e578) && (DAT_0065e570 < iVar5 + DAT_0065ec0c)) &&
        (local_24 < DAT_0065e57c)) && (DAT_0065e574 < local_2c)) {
      puVar6 = (ushort *)(sVar4 * 2 + _DAT_0065ec34 + DAT_0065ec4c);
      uVar2 = *puVar6;
      local_38 = (uint)puVar6[1] - (uint)uVar2;
      iVar7 = (int)(uint)uVar2 >> 3;
      FUN_0048f774(DAT_0065ec44,local_44 * DAT_0065ec60,
                   CONCAT11((char)(uVar2 >> 8),(undefined1)DAT_0065ec14));
      if (DAT_0065ec14 == 0xff) {
        local_34 = 1;
      }
      if (sVar4 == 0x20) {
        local_38 = -1;
      }
      if (((byte)DAT_0065ec54 & 1) != 0) {
        local_c = (byte *)(iVar7 + iVar10 + 0x1a);
        puVar11 = (undefined1 *)
                  (DAT_0065ec60 * DAT_0065ec5c + DAT_0065ec44 + DAT_0065ec58 + local_40);
        for (iVar14 = DAT_0065ec0c; iVar14 != 0; iVar14 = iVar14 + -1) {
          iVar12 = 0;
          uVar8 = 0x80 >> ((byte)uVar2 & 7);
          puVar15 = puVar11;
          local_10 = local_c;
          if (local_38 < 1) {
            bVar9 = 0;
          }
          else {
            bVar9 = *local_c;
          }
          while (iVar13 = iVar12 + 1, iVar12 < (int)local_1c) {
            if (((byte)uVar8 & bVar9) != 0) {
              *puVar15 = DAT_0051dc14;
            }
            puVar15 = puVar15 + 1;
            iVar12 = iVar13;
            if (iVar13 < local_38) {
              bVar3 = (byte)uVar8 >> 1;
              uVar8 = (uint)bVar3;
              if (bVar3 == 0) {
                uVar8 = 0x80;
                bVar9 = local_10[1];
                local_10 = local_10 + 1;
              }
            }
            else {
              bVar9 = 0;
            }
          }
          puVar11 = puVar11 + DAT_0065ec60;
          if (local_c != (byte *)0x0) {
            local_c = local_c + DAT_0065ec30;
          }
        }
      }
      local_c = (byte *)(iVar7 + iVar10 + 0x1a);
      puVar11 = (undefined1 *)(DAT_0065ec44 + local_40);
      DAT_0065ec68 = DAT_0065ec64;
      for (iVar10 = DAT_0065ec0c; iVar10 != 0; iVar10 = iVar10 + -1) {
        iVar7 = 0;
        uVar8 = 0x80 >> ((byte)uVar2 & 7);
        if (local_38 < 1) {
          bVar9 = 0;
        }
        else {
          bVar9 = *local_c;
        }
        puVar15 = puVar11;
        local_10 = local_c;
        if ((uVar1 & 0xff) != 0) {
          do {
            if (((byte)uVar8 & bVar9) != 0) {
              *puVar15 = *DAT_0065ec68;
            }
            puVar15 = puVar15 + 1;
            iVar7 = iVar7 + 1;
            if (iVar7 < local_38) {
              bVar3 = (byte)uVar8 >> 1;
              uVar8 = (uint)bVar3;
              if (bVar3 == 0) {
                uVar8 = 0x80;
                local_10 = local_10 + 1;
                bVar9 = *local_10;
              }
            }
            else {
              bVar9 = 0;
            }
          } while (iVar7 < (int)local_1c);
        }
        puVar11 = puVar11 + DAT_0065ec60;
        if (local_c != (byte *)0x0) {
          local_c = local_c + DAT_0065ec30;
        }
        DAT_0065ec68 = DAT_0065ec68 + 4;
      }
      if (iVar5 < DAT_0065e570) {
        iVar10 = DAT_0065e570 - iVar5;
      }
      else {
        iVar10 = 0;
      }
      if (DAT_0065e578 < local_28) {
        local_44 = DAT_0065e578 - iVar5;
      }
      if (local_24 < DAT_0065e574) {
        iVar7 = DAT_0065e574 - local_24;
      }
      else {
        iVar7 = 0;
      }
      if (DAT_0065e57c < local_2c) {
        local_2c = local_2c - DAT_0065e57c;
      }
      else {
        local_2c = 0;
      }
      iVar14 = DAT_0065e574;
      if (DAT_0065e574 < local_24) {
        iVar14 = local_24;
      }
      local_44 = local_44 - iVar10;
      iVar13 = iVar10 * DAT_0065ec60 + iVar7 + DAT_0065ec44;
      iVar12 = iVar7 + local_2c + (DAT_0065ec60 - local_48);
      iVar7 = local_48 - (iVar7 + local_2c);
      if ((0 < local_44) && (0 < iVar7)) {
        FUN_00499840(iVar14,iVar5 + iVar10);
        if ((DAT_0051e35c == 0x100008) || (DAT_0051e35c == 0x100010)) {
          if (local_34 == 0) {
            if ((&PTR_LAB_0051e2b0)[DAT_0065ec50] != (undefined *)0x0) {
              (*(code *)(&PTR_LAB_0051e2b0)[DAT_0065ec50])
                        (iVar13,local_44,iVar7,iVar12,DAT_0051dc20 + 8,DAT_0051c3c4,DAT_0051c3c0);
            }
          }
          else if ((&PTR_LAB_0051e310)[DAT_0065ec50] != (undefined *)0x0) {
            (*(code *)(&PTR_LAB_0051e310)[DAT_0065ec50])
                      (iVar13,local_44,iVar7,iVar12,DAT_0051dc20 + 8,DAT_0051c3c4,DAT_0051c3c0);
          }
        }
        else if (local_34 == 0) {
          if (*(int *)(DAT_0069ee94 + DAT_0065ec50 * 4) != 0) {
            (**(code **)(DAT_0069ee94 + DAT_0065ec50 * 4))
                      (iVar13,local_44,iVar7,iVar12,DAT_0051c3c4,DAT_0051c3c0);
          }
        }
        else if (*(int *)(DAT_0069ee98 + DAT_0065ec50 * 4) != 0) {
          (**(code **)(DAT_0069ee98 + DAT_0065ec50 * 4))
                    (iVar13,local_44,iVar7,iVar12,DAT_0051c3c4,DAT_0051c3c0);
        }
      }
    }
  }
  return;
}

