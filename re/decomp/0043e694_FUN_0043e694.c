// FUN_0043e694 @ 0043e694 size=1813 sig=undefined FUN_0043e694() cc=unknown
// callers: FUN_00440b68
// callees: FUN_0048d03e

void FUN_0043e694(int param_1,int param_2,byte *param_3,char *param_4)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  int *local_90;
  undefined2 *local_88;
  int local_84;
  undefined2 *local_7c;
  int local_78;
  int local_74;
  undefined2 *local_6c;
  int local_68;
  int local_64;
  undefined2 *local_5c;
  int local_58;
  int local_54;
  byte *local_48;
  int local_44;
  int local_40;
  int local_38;
  int local_30;
  byte *local_28;
  int local_24;
  int local_20;
  int local_14;
  byte *local_10;
  uint local_c;
  int local_8;
  
  iVar8 = *DAT_0051bddc;
  iVar10 = DAT_0051bddc[4];
  if (DAT_0051bddc[3] == 8) {
    local_c = 0;
    do {
      local_10 = param_3;
      if ((local_c & 1) == 0) {
        local_14 = 0x1e;
        if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
          local_20 = (int)*param_4;
          local_24 = param_2 - local_20;
          if ((int)(&DAT_006552cc)[param_1] <= param_2) {
            local_20 = local_20 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
          }
          if (local_24 < DAT_00559dec) {
            local_20 = local_20 - (DAT_00559dec - local_24);
            local_24 = DAT_00559dec;
          }
          if (-1 < local_20) {
            (&DAT_006552cc)[param_1] = local_24;
            local_28 = (byte *)FUN_0048d03e(DAT_0051bddc,param_1,local_24);
            bVar1 = *param_3;
            while (-1 < local_20) {
              *local_28 = bVar1;
              local_28 = local_28 + DAT_00583e14;
              local_20 = local_20 + -1;
            }
          }
        }
        local_10 = param_3 + 1;
        iVar8 = param_1 + 1;
        iVar10 = param_2 + 1;
        pcVar12 = param_4 + 1;
      }
      else {
        local_14 = 0x20;
        iVar8 = param_1;
        iVar10 = param_2;
        pcVar12 = param_4;
      }
      local_90 = &DAT_006552cc + iVar8;
      local_8 = 0;
      if (local_14 >> 1 != 0) {
        do {
          if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
            local_30 = (int)*pcVar12;
            iVar3 = iVar10 - local_30;
            if (*local_90 <= iVar10) {
              local_30 = local_30 - ((iVar10 - *local_90) + 1);
            }
            if (iVar3 < DAT_00559dec) {
              local_30 = local_30 - (DAT_00559dec - iVar3);
              iVar3 = DAT_00559dec;
            }
            if (-1 < local_30) {
              *local_90 = iVar3;
              pbVar4 = (byte *)FUN_0048d03e(DAT_0051bddc,iVar8,iVar3);
              bVar1 = *local_10;
              while (-1 < local_30) {
                *pbVar4 = bVar1;
                pbVar4 = pbVar4 + DAT_00583e14;
                local_30 = local_30 + -1;
              }
            }
          }
          piVar6 = local_90 + 1;
          iVar3 = iVar8 + 1;
          if ((DAT_00559de8 <= iVar3) && (iVar3 < DAT_00559df0)) {
            local_38 = (int)pcVar12[1];
            iVar5 = iVar10 - local_38;
            if (*piVar6 <= iVar10) {
              local_38 = local_38 - ((iVar10 - *piVar6) + 1);
            }
            if (iVar5 < DAT_00559dec) {
              local_38 = local_38 - (DAT_00559dec - iVar5);
              iVar5 = DAT_00559dec;
            }
            if (-1 < local_38) {
              *piVar6 = iVar5;
              pbVar4 = (byte *)FUN_0048d03e(DAT_0051bddc,iVar3,iVar5);
              bVar1 = local_10[1];
              while (-1 < local_38) {
                *pbVar4 = bVar1;
                pbVar4 = pbVar4 + DAT_00583e14;
                local_38 = local_38 + -1;
              }
            }
          }
          local_90 = local_90 + 2;
          local_10 = local_10 + 2;
          local_8 = local_8 + 1;
          iVar8 = iVar8 + 2;
          iVar10 = iVar10 + 1;
          pcVar12 = pcVar12 + 2;
        } while (local_8 < local_14 >> 1);
      }
      if ((local_c & 1) == 0) {
        if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
          local_40 = (int)*pcVar12;
          local_44 = iVar10 - local_40;
          if ((int)(&DAT_006552cc)[iVar8] <= iVar10) {
            local_40 = local_40 - ((iVar10 - (&DAT_006552cc)[iVar8]) + 1);
          }
          if (local_44 < DAT_00559dec) {
            local_40 = local_40 - (DAT_00559dec - local_44);
            local_44 = DAT_00559dec;
          }
          if (-1 < local_40) {
            (&DAT_006552cc)[iVar8] = local_44;
            local_48 = (byte *)FUN_0048d03e(DAT_0051bddc,iVar8,local_44);
            bVar1 = *local_10;
            while (-1 < local_40) {
              *local_48 = bVar1;
              local_48 = local_48 + DAT_00583e14;
              local_40 = local_40 + -1;
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
      local_c = local_c + 1;
    } while ((int)local_c < 0x20);
  }
  else {
    iVar3 = DAT_0058df44 + 8;
    local_c = 0;
    do {
      local_10 = param_3;
      if ((local_c & 1) == 0) {
        local_14 = 0x1e;
        if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
          local_54 = (int)*param_4;
          local_58 = param_2 - local_54;
          if ((int)(&DAT_006552cc)[param_1] <= param_2) {
            local_54 = local_54 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
          }
          if (local_58 < DAT_00559dec) {
            local_54 = local_54 - (DAT_00559dec - local_58);
            local_58 = DAT_00559dec;
          }
          if (-1 < local_54) {
            (&DAT_006552cc)[param_1] = local_58;
            local_5c = (undefined2 *)(iVar10 * local_58 + iVar8 + param_1 * 2);
            uVar2 = *(undefined2 *)(iVar3 + (uint)*param_3 * 2);
            while (-1 < local_54) {
              *local_5c = uVar2;
              local_5c = (undefined2 *)((int)local_5c + DAT_0051c3c0);
              local_54 = local_54 + -1;
            }
          }
        }
        local_10 = param_3 + 1;
        iVar5 = param_1 + 1;
        iVar11 = param_2 + 1;
        pcVar12 = param_4 + 1;
      }
      else {
        local_14 = 0x20;
        iVar5 = param_1;
        iVar11 = param_2;
        pcVar12 = param_4;
      }
      local_8 = 0;
      piVar6 = &DAT_006552cc + iVar5;
      if (local_14 >> 1 != 0) {
        do {
          if ((DAT_00559de8 <= iVar5) && (iVar5 < DAT_00559df0)) {
            local_64 = (int)*pcVar12;
            local_68 = iVar11 - local_64;
            if (*piVar6 <= iVar11) {
              local_64 = local_64 - ((iVar11 - *piVar6) + 1);
            }
            if (local_68 < DAT_00559dec) {
              local_64 = local_64 - (DAT_00559dec - local_68);
              local_68 = DAT_00559dec;
            }
            if (-1 < local_64) {
              *piVar6 = local_68;
              local_6c = (undefined2 *)(iVar10 * local_68 + iVar8 + iVar5 * 2);
              uVar2 = *(undefined2 *)(iVar3 + (uint)*local_10 * 2);
              while (-1 < local_64) {
                *local_6c = uVar2;
                local_6c = (undefined2 *)((int)local_6c + DAT_0051c3c0);
                local_64 = local_64 + -1;
              }
            }
          }
          iVar9 = iVar5 + 1;
          piVar7 = piVar6 + 1;
          if ((DAT_00559de8 <= iVar9) && (iVar9 < DAT_00559df0)) {
            local_74 = (int)pcVar12[1];
            local_78 = iVar11 - local_74;
            if (*piVar7 <= iVar11) {
              local_74 = local_74 - ((iVar11 - *piVar7) + 1);
            }
            if (local_78 < DAT_00559dec) {
              local_74 = local_74 - (DAT_00559dec - local_78);
              local_78 = DAT_00559dec;
            }
            if (-1 < local_74) {
              *piVar7 = local_78;
              local_7c = (undefined2 *)(iVar10 * local_78 + iVar8 + iVar9 * 2);
              uVar2 = *(undefined2 *)(iVar3 + (uint)local_10[1] * 2);
              while (-1 < local_74) {
                *local_7c = uVar2;
                local_7c = (undefined2 *)((int)local_7c + DAT_0051c3c0);
                local_74 = local_74 + -1;
              }
            }
          }
          iVar11 = iVar11 + 1;
          iVar5 = iVar5 + 2;
          piVar6 = piVar6 + 2;
          local_10 = local_10 + 2;
          pcVar12 = pcVar12 + 2;
          local_8 = local_8 + 1;
        } while (local_8 < local_14 >> 1);
      }
      if ((local_c & 1) == 0) {
        if ((DAT_00559de8 <= iVar5) && (iVar5 < DAT_00559df0)) {
          iVar9 = (int)*pcVar12;
          local_84 = iVar11 - iVar9;
          if ((int)(&DAT_006552cc)[iVar5] <= iVar11) {
            iVar9 = iVar9 - ((iVar11 - (&DAT_006552cc)[iVar5]) + 1);
          }
          if (local_84 < DAT_00559dec) {
            iVar9 = iVar9 - (DAT_00559dec - local_84);
            local_84 = DAT_00559dec;
          }
          if (-1 < iVar9) {
            (&DAT_006552cc)[iVar5] = local_84;
            local_88 = (undefined2 *)(iVar10 * local_84 + iVar8 + iVar5 * 2);
            uVar2 = *(undefined2 *)(iVar3 + (uint)*local_10 * 2);
            while (-1 < iVar9) {
              *local_88 = uVar2;
              local_88 = (undefined2 *)((int)local_88 + DAT_0051c3c0);
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
      local_c = local_c + 1;
    } while ((int)local_c < 0x20);
  }
  return;
}

