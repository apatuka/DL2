// FUN_0043febc @ 0043febc size=2008 sig=undefined FUN_0043febc() cc=unknown
// callers: FUN_00440b68
// callees: FUN_00488429

void FUN_0043febc(int param_1,int param_2,byte *param_3,char *param_4,int param_5,uint param_6,
                 int param_7)

{
  int *piVar1;
  byte bVar2;
  char cVar3;
  undefined2 uVar4;
  uint uVar5;
  uint *puVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *local_b4;
  undefined2 *local_ac;
  int local_a8;
  uint local_a4 [2];
  undefined2 *local_9c;
  int local_98;
  int local_94;
  uint local_90 [2];
  undefined2 *local_88;
  int local_84;
  int local_80;
  uint local_7c [3];
  undefined2 *local_70;
  int local_6c;
  int local_68;
  uint local_64 [3];
  uint local_58 [3];
  uint local_4c;
  uint local_48 [3];
  uint local_3c;
  byte *local_38;
  int local_34;
  uint local_30;
  int local_2c;
  int local_28;
  undefined *local_24;
  int local_20;
  int local_1c;
  char *local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_1c = *DAT_0051bddc;
  local_20 = DAT_0051bddc[4];
  local_28 = (param_6 & 3) * 0x20;
  local_2c = ((int)param_6 >> 2) * 0x20;
  local_30 = param_1 + param_2 + param_6;
  local_34 = (local_30 & 1) + param_7 * 2;
  local_24 = PTR_DAT_004d0348 + local_34 * 0x10;
  local_38 = (byte *)(*(int *)(local_24 + 8) + local_28 + *(short *)(local_24 + 4) * local_2c +
                     0xf80);
  if (DAT_0051bddc[3] == 8) {
    local_c = 0;
    do {
      local_18 = param_4;
      local_10 = param_2;
      if ((local_c & 1) == 0) {
        if (*local_38 == 0) {
          bVar2 = *param_3;
        }
        else {
          bVar2 = *local_38;
        }
        local_3c = 7;
        local_48[2] = (bVar2 & 7) + param_5;
        if ((int)local_48[2] < 7) {
          puVar6 = local_48 + 2;
        }
        else {
          puVar6 = &local_3c;
        }
        pbVar7 = local_38 + 1;
        local_18 = param_4 + 1;
        local_10 = param_2 + 1;
        FUN_00488429(param_1,param_2,(int)*param_4,bVar2 & 0xf8 | *puVar6);
        local_14 = 0x1e;
        pbVar8 = param_3 + 1;
        iVar10 = param_1 + 1;
      }
      else {
        local_14 = 0x20;
        pbVar7 = local_38;
        pbVar8 = param_3;
        iVar10 = param_1;
      }
      local_14 = local_14 >> 1;
      local_8 = 0;
      if (local_14 != 0) {
        do {
          if (*pbVar7 == 0) {
            local_48[1] = 7;
            local_48[0] = (*pbVar8 & 7) + param_5;
            if ((int)local_48[0] < 7) {
              puVar6 = local_48;
            }
            else {
              puVar6 = local_48 + 1;
            }
            uVar5 = *pbVar8 & 0xf8 | *puVar6;
          }
          else {
            uVar5 = (uint)*pbVar7;
          }
          cVar3 = *local_18;
          iVar9 = iVar10 + 1;
          local_18 = local_18 + 1;
          FUN_00488429(iVar10,local_10,(int)cVar3,uVar5);
          iVar11 = local_10;
          if (pbVar7[1] == 0) {
            local_4c = 7;
            local_58[2] = (pbVar8[1] & 7) + param_5;
            if ((int)local_58[2] < 7) {
              puVar6 = local_58 + 2;
            }
            else {
              puVar6 = &local_4c;
            }
            uVar5 = pbVar8[1] & 0xf8 | *puVar6;
          }
          else {
            uVar5 = (uint)pbVar7[1];
          }
          pbVar7 = pbVar7 + 2;
          cVar3 = *local_18;
          pbVar8 = pbVar8 + 2;
          local_10 = local_10 + 1;
          iVar10 = iVar10 + 2;
          local_18 = local_18 + 1;
          FUN_00488429(iVar9,iVar11,(int)cVar3,uVar5);
          local_8 = local_8 + 1;
        } while (local_8 < local_14);
      }
      if ((local_c & 1) == 0) {
        if (*pbVar7 == 0) {
          local_58[1] = 7;
          local_58[0] = (*pbVar8 & 7) + param_5;
          if ((int)local_58[0] < 7) {
            puVar6 = local_58;
          }
          else {
            puVar6 = local_58 + 1;
          }
          uVar5 = *pbVar8 & 0xf8 | *puVar6;
        }
        else {
          uVar5 = (uint)*pbVar7;
        }
        FUN_00488429(iVar10,local_10,(int)*local_18,uVar5);
      }
      else {
        param_2 = param_2 + -1;
      }
      param_1 = param_1 + 1;
      param_4 = param_4 + -DAT_0058f140;
      param_3 = param_3 + -DAT_0058f140;
      local_38 = local_38 + -0x80;
      local_c = local_c + 1;
    } while ((int)local_c < 0x20);
  }
  else {
    iVar10 = DAT_0058df44 + 8;
    local_c = 0;
    do {
      local_18 = param_4;
      local_10 = param_2;
      if ((local_c & 1) == 0) {
        if (*local_38 == 0xff) {
          bVar2 = *param_3;
        }
        else {
          bVar2 = *local_38;
        }
        local_64[1] = 7;
        local_64[0] = (bVar2 & 7) + param_5;
        if ((int)local_64[0] < 7) {
          puVar6 = local_64;
        }
        else {
          puVar6 = local_64 + 1;
        }
        uVar5 = *puVar6;
        if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
          local_68 = (int)*param_4;
          local_6c = param_2 - local_68;
          if ((int)(&DAT_006552cc)[param_1] <= param_2) {
            local_68 = local_68 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
          }
          if (local_6c < DAT_00559dec) {
            local_68 = local_68 - (DAT_00559dec - local_6c);
            local_6c = DAT_00559dec;
          }
          if (-1 < local_68) {
            (&DAT_006552cc)[param_1] = local_6c;
            local_70 = (undefined2 *)(local_20 * local_6c + local_1c + param_1 * 2);
            uVar4 = *(undefined2 *)(iVar10 + (bVar2 & 0xf8 | uVar5) * 2);
            while (-1 < local_68) {
              *local_70 = uVar4;
              local_70 = (undefined2 *)((int)local_70 + DAT_0051c3c0);
              local_68 = local_68 + -1;
            }
          }
        }
        local_10 = param_2 + 1;
        local_18 = param_4 + 1;
        local_14 = 0x1e;
        pbVar7 = local_38 + 1;
        pbVar8 = param_3 + 1;
        iVar11 = param_1 + 1;
      }
      else {
        local_14 = 0x20;
        pbVar7 = local_38;
        pbVar8 = param_3;
        iVar11 = param_1;
      }
      local_8 = 0;
      local_b4 = &DAT_006552cc + iVar11;
      if (local_14 >> 1 != 0) {
        do {
          if (*pbVar7 == 0xff) {
            local_7c[1] = 7;
            local_7c[0] = (*pbVar8 & 7) + param_5;
            if ((int)local_7c[0] < 7) {
              puVar6 = local_7c;
            }
            else {
              puVar6 = local_7c + 1;
            }
            uVar5 = *pbVar8 & 0xf8 | *puVar6;
          }
          else {
            uVar5 = (uint)*pbVar7;
          }
          if ((DAT_00559de8 <= iVar11) && (iVar11 < DAT_00559df0)) {
            local_80 = (int)*local_18;
            local_84 = local_10 - local_80;
            if (*local_b4 <= local_10) {
              local_80 = local_80 - ((local_10 - *local_b4) + 1);
            }
            if (local_84 < DAT_00559dec) {
              local_80 = local_80 - (DAT_00559dec - local_84);
              local_84 = DAT_00559dec;
            }
            if (-1 < local_80) {
              *local_b4 = local_84;
              local_88 = (undefined2 *)(local_20 * local_84 + local_1c + iVar11 * 2);
              uVar4 = *(undefined2 *)(iVar10 + uVar5 * 2);
              while (-1 < local_80) {
                *local_88 = uVar4;
                local_88 = (undefined2 *)((int)local_88 + DAT_0051c3c0);
                local_80 = local_80 + -1;
              }
            }
          }
          piVar1 = local_b4 + 1;
          iVar9 = iVar11 + 1;
          if (pbVar7[1] == 0xff) {
            local_90[1] = 7;
            local_90[0] = (pbVar8[1] & 7) + param_5;
            if ((int)local_90[0] < 7) {
              puVar6 = local_90;
            }
            else {
              puVar6 = local_90 + 1;
            }
            uVar5 = pbVar8[1] & 0xf8 | *puVar6;
          }
          else {
            uVar5 = (uint)pbVar7[1];
          }
          pbVar7 = pbVar7 + 2;
          pbVar8 = pbVar8 + 2;
          if ((DAT_00559de8 <= iVar9) && (iVar9 < DAT_00559df0)) {
            local_94 = (int)local_18[1];
            local_98 = local_10 - local_94;
            if (*piVar1 <= local_10) {
              local_94 = local_94 - ((local_10 - *piVar1) + 1);
            }
            if (local_98 < DAT_00559dec) {
              local_94 = local_94 - (DAT_00559dec - local_98);
              local_98 = DAT_00559dec;
            }
            if (-1 < local_94) {
              *piVar1 = local_98;
              local_9c = (undefined2 *)(local_20 * local_98 + local_1c + iVar9 * 2);
              uVar4 = *(undefined2 *)(iVar10 + uVar5 * 2);
              while (-1 < local_94) {
                *local_9c = uVar4;
                local_9c = (undefined2 *)((int)local_9c + DAT_0051c3c0);
                local_94 = local_94 + -1;
              }
            }
          }
          local_10 = local_10 + 1;
          iVar11 = iVar11 + 2;
          local_b4 = local_b4 + 2;
          local_18 = local_18 + 2;
          local_8 = local_8 + 1;
        } while (local_8 < local_14 >> 1);
      }
      if ((local_c & 1) == 0) {
        if (*pbVar7 == 0xff) {
          local_a4[1] = 7;
          local_a4[0] = (*pbVar8 & 7) + param_5;
          if ((int)local_a4[0] < 7) {
            puVar6 = local_a4;
          }
          else {
            puVar6 = local_a4 + 1;
          }
          uVar5 = *pbVar8 & 0xf8 | *puVar6;
        }
        else {
          uVar5 = (uint)*pbVar7;
        }
        if ((DAT_00559de8 <= iVar11) && (iVar11 < DAT_00559df0)) {
          iVar9 = (int)*local_18;
          local_a8 = local_10 - iVar9;
          if ((int)(&DAT_006552cc)[iVar11] <= local_10) {
            iVar9 = iVar9 - ((local_10 - (&DAT_006552cc)[iVar11]) + 1);
          }
          if (local_a8 < DAT_00559dec) {
            iVar9 = iVar9 - (DAT_00559dec - local_a8);
            local_a8 = DAT_00559dec;
          }
          if (-1 < iVar9) {
            (&DAT_006552cc)[iVar11] = local_a8;
            local_ac = (undefined2 *)(local_20 * local_a8 + local_1c + iVar11 * 2);
            uVar4 = *(undefined2 *)(iVar10 + uVar5 * 2);
            while (-1 < iVar9) {
              *local_ac = uVar4;
              local_ac = (undefined2 *)((int)local_ac + DAT_0051c3c0);
              iVar9 = iVar9 + -1;
            }
          }
        }
      }
      else {
        param_2 = param_2 + -1;
      }
      param_1 = param_1 + 1;
      param_4 = param_4 + -DAT_0058f140;
      param_3 = param_3 + -DAT_0058f140;
      local_38 = local_38 + -0x80;
      local_c = local_c + 1;
    } while ((int)local_c < 0x20);
  }
  return;
}

