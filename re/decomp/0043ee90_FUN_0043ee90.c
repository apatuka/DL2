// FUN_0043ee90 @ 0043ee90 size=2504 sig=undefined FUN_0043ee90() cc=unknown
// callers: FUN_00440b68
// callees: FUN_00488429

void FUN_0043ee90(int param_1,int param_2,byte *param_3,char *param_4,uint param_5,int param_6)

{
  undefined2 uVar1;
  char *pcVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  undefined2 *local_b8;
  int local_b4;
  int local_b0;
  undefined2 *local_a8;
  int local_a4;
  int local_a0;
  undefined2 *local_98;
  int local_94;
  int local_90;
  undefined2 *local_88;
  int local_84;
  int local_80;
  undefined2 *local_78;
  int local_74;
  int local_70;
  undefined2 *local_68;
  int local_64;
  int local_60;
  undefined2 *local_58;
  int local_54;
  int local_50;
  undefined2 *local_48;
  int local_44;
  int local_40;
  byte *local_38;
  char *local_18;
  byte *local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  iVar6 = *DAT_0051bddc;
  iVar9 = DAT_0051bddc[4];
  iVar5 = (param_1 * param_2 * param_5 & 1) + param_6 * 2;
  local_38 = (byte *)(*(int *)(PTR_DAT_004d0348 + iVar5 * 0x10 + 8) + (param_5 & 3) * 0x20 +
                      (int)*(short *)(PTR_DAT_004d0348 + iVar5 * 0x10 + 4) *
                      ((int)param_5 >> 2) * 0x20 + 0xf80);
  if (DAT_0051bddc[3] == 8) {
    local_c = 0;
    do {
      local_18 = param_4;
      local_14 = param_3;
      if ((local_c & 1) == 0) {
        if (*local_38 == 0) {
          FUN_00488429(param_1,param_2,(int)*param_4,(int)(char)*param_3);
        }
        else {
          FUN_00488429(param_1,param_2,(int)*param_4,(int)(char)*local_38);
        }
        local_18 = param_4 + 1;
        local_14 = param_3 + 1;
        local_10 = 0x1e;
        iVar6 = param_1 + 1;
        iVar9 = param_2 + 1;
        pbVar11 = local_38 + 1;
      }
      else {
        local_10 = 0x20;
        iVar6 = param_1;
        iVar9 = param_2;
        pbVar11 = local_38;
      }
      local_8 = 0;
      if (local_10 >> 1 != 0) {
        do {
          pcVar2 = local_18;
          if (*pbVar11 == 0) {
            FUN_00488429(iVar6,iVar9,(int)*local_18,(int)(char)*local_14);
          }
          else {
            FUN_00488429(iVar6,iVar9,(int)*local_18,(int)(char)*pbVar11);
          }
          local_18 = local_18 + 1;
          if (pbVar11[1] == 0) {
            FUN_00488429(iVar6 + 1,iVar9,(int)*local_18,(int)(char)local_14[1]);
          }
          else {
            FUN_00488429(iVar6 + 1,iVar9,(int)*local_18,(int)(char)pbVar11[1]);
          }
          local_18 = pcVar2 + 2;
          iVar9 = iVar9 + 1;
          iVar6 = iVar6 + 2;
          pbVar11 = pbVar11 + 2;
          local_14 = local_14 + 2;
          local_8 = local_8 + 1;
        } while (local_8 < local_10 >> 1);
      }
      if ((local_c & 1) == 0) {
        if (*pbVar11 == 0) {
          FUN_00488429(iVar6,iVar9,(int)*local_18,(int)(char)*local_14);
        }
        else {
          FUN_00488429(iVar6,iVar9,(int)*local_18,(int)(char)*pbVar11);
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
  else {
    iVar5 = DAT_0058df44 + 8;
    local_c = 0;
    do {
      local_14 = param_3;
      if ((local_c & 1) == 0) {
        if (*local_38 == 0xff) {
          if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
            local_50 = (int)*param_4;
            local_54 = param_2 - local_50;
            if ((int)(&DAT_006552cc)[param_1] <= param_2) {
              local_50 = local_50 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
            }
            if (local_54 < DAT_00559dec) {
              local_50 = local_50 - (DAT_00559dec - local_54);
              local_54 = DAT_00559dec;
            }
            if (-1 < local_50) {
              (&DAT_006552cc)[param_1] = local_54;
              local_58 = (undefined2 *)(iVar9 * local_54 + iVar6 + param_1 * 2);
              uVar1 = *(undefined2 *)(iVar5 + (uint)*param_3 * 2);
              while (-1 < local_50) {
                *local_58 = uVar1;
                local_58 = (undefined2 *)((int)local_58 + DAT_0051c3c0);
                local_50 = local_50 + -1;
              }
            }
          }
        }
        else if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
          local_40 = (int)*param_4;
          local_44 = param_2 - local_40;
          if ((int)(&DAT_006552cc)[param_1] <= param_2) {
            local_40 = local_40 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
          }
          if (local_44 < DAT_00559dec) {
            local_40 = local_40 - (DAT_00559dec - local_44);
            local_44 = DAT_00559dec;
          }
          if (-1 < local_40) {
            (&DAT_006552cc)[param_1] = local_44;
            local_48 = (undefined2 *)(iVar9 * local_44 + iVar6 + param_1 * 2);
            uVar1 = *(undefined2 *)(iVar5 + (uint)*local_38 * 2);
            while (-1 < local_40) {
              *local_48 = uVar1;
              local_48 = (undefined2 *)((int)local_48 + DAT_0051c3c0);
              local_40 = local_40 + -1;
            }
          }
        }
        local_14 = param_3 + 1;
        local_10 = 0x1e;
        iVar8 = param_1 + 1;
        iVar10 = param_2 + 1;
        pbVar11 = local_38 + 1;
      }
      else {
        local_10 = 0x20;
        iVar8 = param_1;
        iVar10 = param_2;
        pbVar11 = local_38;
      }
      local_8 = 0;
      piVar3 = &DAT_006552cc + iVar8;
      if (local_10 >> 1 != 0) {
        do {
          if (*pbVar11 == 0xff) {
            if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
              local_70 = (int)*param_4;
              local_74 = iVar10 - local_70;
              if (*piVar3 <= iVar10) {
                local_70 = local_70 - ((iVar10 - *piVar3) + 1);
              }
              if (local_74 < DAT_00559dec) {
                local_70 = local_70 - (DAT_00559dec - local_74);
                local_74 = DAT_00559dec;
              }
              if (-1 < local_70) {
                *piVar3 = local_74;
                local_78 = (undefined2 *)(iVar9 * local_74 + iVar6 + iVar8 * 2);
                uVar1 = *(undefined2 *)(iVar5 + (uint)*local_14 * 2);
                while (-1 < local_70) {
                  *local_78 = uVar1;
                  local_78 = (undefined2 *)((int)local_78 + DAT_0051c3c0);
                  local_70 = local_70 + -1;
                }
              }
            }
          }
          else if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
            local_60 = (int)*param_4;
            local_64 = iVar10 - local_60;
            if (*piVar3 <= iVar10) {
              local_60 = local_60 - ((iVar10 - *piVar3) + 1);
            }
            if (local_64 < DAT_00559dec) {
              local_60 = local_60 - (DAT_00559dec - local_64);
              local_64 = DAT_00559dec;
            }
            if (-1 < local_60) {
              *piVar3 = local_64;
              local_68 = (undefined2 *)(iVar9 * local_64 + iVar6 + iVar8 * 2);
              uVar1 = *(undefined2 *)(iVar5 + (uint)*pbVar11 * 2);
              while (-1 < local_60) {
                *local_68 = uVar1;
                local_68 = (undefined2 *)((int)local_68 + DAT_0051c3c0);
                local_60 = local_60 + -1;
              }
            }
          }
          iVar7 = iVar8 + 1;
          piVar4 = piVar3 + 1;
          if (pbVar11[1] == 0xff) {
            if ((DAT_00559de8 <= iVar7) && (iVar7 < DAT_00559df0)) {
              local_90 = (int)*param_4;
              local_94 = iVar10 - local_90;
              if (*piVar4 <= iVar10) {
                local_90 = local_90 - ((iVar10 - *piVar4) + 1);
              }
              if (local_94 < DAT_00559dec) {
                local_90 = local_90 - (DAT_00559dec - local_94);
                local_94 = DAT_00559dec;
              }
              if (-1 < local_90) {
                *piVar4 = local_94;
                local_98 = (undefined2 *)(iVar9 * local_94 + iVar6 + iVar7 * 2);
                uVar1 = *(undefined2 *)(iVar5 + (uint)local_14[1] * 2);
                while (-1 < local_90) {
                  *local_98 = uVar1;
                  local_98 = (undefined2 *)((int)local_98 + DAT_0051c3c0);
                  local_90 = local_90 + -1;
                }
              }
            }
          }
          else if ((DAT_00559de8 <= iVar7) && (iVar7 < DAT_00559df0)) {
            local_80 = (int)*param_4;
            local_84 = iVar10 - local_80;
            if (*piVar4 <= iVar10) {
              local_80 = local_80 - ((iVar10 - *piVar4) + 1);
            }
            if (local_84 < DAT_00559dec) {
              local_80 = local_80 - (DAT_00559dec - local_84);
              local_84 = DAT_00559dec;
            }
            if (-1 < local_80) {
              *piVar4 = local_84;
              local_88 = (undefined2 *)(iVar9 * local_84 + iVar6 + iVar7 * 2);
              uVar1 = *(undefined2 *)(iVar5 + (uint)pbVar11[1] * 2);
              while (-1 < local_80) {
                *local_88 = uVar1;
                local_88 = (undefined2 *)((int)local_88 + DAT_0051c3c0);
                local_80 = local_80 + -1;
              }
            }
          }
          iVar10 = iVar10 + 1;
          iVar8 = iVar8 + 2;
          piVar3 = piVar3 + 2;
          pbVar11 = pbVar11 + 2;
          local_14 = local_14 + 2;
          local_8 = local_8 + 1;
        } while (local_8 < local_10 >> 1);
      }
      if ((local_c & 1) == 0) {
        if (*pbVar11 == 0xff) {
          if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
            local_b0 = (int)*param_4;
            local_b4 = iVar10 - local_b0;
            if ((int)(&DAT_006552cc)[iVar8] <= iVar10) {
              local_b0 = local_b0 - ((iVar10 - (&DAT_006552cc)[iVar8]) + 1);
            }
            if (local_b4 < DAT_00559dec) {
              local_b0 = local_b0 - (DAT_00559dec - local_b4);
              local_b4 = DAT_00559dec;
            }
            if (-1 < local_b0) {
              (&DAT_006552cc)[iVar8] = local_b4;
              local_b8 = (undefined2 *)(iVar9 * local_b4 + iVar6 + iVar8 * 2);
              uVar1 = *(undefined2 *)(iVar5 + (uint)*local_14 * 2);
              while (-1 < local_b0) {
                *local_b8 = uVar1;
                local_b8 = (undefined2 *)((int)local_b8 + DAT_0051c3c0);
                local_b0 = local_b0 + -1;
              }
            }
          }
        }
        else if ((DAT_00559de8 <= iVar8) && (iVar8 < DAT_00559df0)) {
          local_a0 = (int)*param_4;
          local_a4 = iVar10 - local_a0;
          if ((int)(&DAT_006552cc)[iVar8] <= iVar10) {
            local_a0 = local_a0 - ((iVar10 - (&DAT_006552cc)[iVar8]) + 1);
          }
          if (local_a4 < DAT_00559dec) {
            local_a0 = local_a0 - (DAT_00559dec - local_a4);
            local_a4 = DAT_00559dec;
          }
          if (-1 < local_a0) {
            (&DAT_006552cc)[iVar8] = local_a4;
            local_a8 = (undefined2 *)(iVar9 * local_a4 + iVar6 + iVar8 * 2);
            uVar1 = *(undefined2 *)(iVar5 + (uint)*pbVar11 * 2);
            while (-1 < local_a0) {
              *local_a8 = uVar1;
              local_a8 = (undefined2 *)((int)local_a8 + DAT_0051c3c0);
              local_a0 = local_a0 + -1;
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

