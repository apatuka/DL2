// FUN_0043f858 @ 0043f858 size=1634 sig=undefined FUN_0043f858() cc=unknown
// callers: FUN_00440b68
// callees: FUN_00488429

void FUN_0043f858(int param_1,int param_2,byte *param_3,char *param_4,int param_5)

{
  char cVar1;
  undefined2 uVar2;
  int *piVar3;
  int *piVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  uint local_9c [3];
  undefined2 *local_90;
  int local_8c;
  uint local_88 [3];
  undefined2 *local_7c;
  int local_78;
  int local_74;
  uint local_70 [3];
  undefined2 *local_64;
  int local_60;
  int local_5c;
  uint local_58 [3];
  undefined2 *local_4c;
  int local_48;
  int local_44;
  uint local_3c [3];
  uint local_30;
  uint local_2c [3];
  uint local_20;
  int local_1c;
  int local_18;
  char *local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_18 = *DAT_0051bddc;
  local_1c = DAT_0051bddc[4];
  if (DAT_0051bddc[3] == 8) {
    local_c = 0;
    do {
      local_14 = param_4;
      if ((local_c & 1) == 0) {
        local_20 = 7;
        local_2c[2] = (*param_3 & 7) + param_5;
        if ((int)local_2c[2] < 7) {
          puVar5 = local_2c + 2;
        }
        else {
          puVar5 = &local_20;
        }
        local_14 = param_4 + 1;
        FUN_00488429(param_1,param_2,(int)*param_4,*param_3 & 0xf8 | *puVar5);
        local_10 = 0x1e;
        iVar7 = param_1 + 1;
        pbVar9 = param_3 + 1;
        iVar10 = param_2 + 1;
      }
      else {
        local_10 = 0x20;
        iVar7 = param_1;
        pbVar9 = param_3;
        iVar10 = param_2;
      }
      local_10 = local_10 >> 1;
      local_8 = 0;
      iVar11 = iVar10;
      if (local_10 != 0) {
        do {
          local_2c[1] = 7;
          local_2c[0] = (*pbVar9 & 7) + param_5;
          if ((int)local_2c[0] < 7) {
            puVar5 = local_2c;
          }
          else {
            puVar5 = local_2c + 1;
          }
          pbVar8 = pbVar9 + 1;
          iVar6 = iVar7 + 1;
          cVar1 = *local_14;
          local_14 = local_14 + 1;
          FUN_00488429(iVar7,iVar11,(int)cVar1,*pbVar9 & 0xf8 | *puVar5);
          local_30 = 7;
          local_3c[2] = (*pbVar8 & 7) + param_5;
          if ((int)local_3c[2] < 7) {
            puVar5 = local_3c + 2;
          }
          else {
            puVar5 = &local_30;
          }
          iVar10 = iVar11 + 1;
          pbVar9 = pbVar9 + 2;
          cVar1 = *local_14;
          iVar7 = iVar7 + 2;
          local_14 = local_14 + 1;
          FUN_00488429(iVar6,iVar11,(int)cVar1,*pbVar8 & 0xf8 | *puVar5);
          local_8 = local_8 + 1;
          iVar11 = iVar10;
        } while (local_8 < local_10);
      }
      if ((local_c & 1) == 0) {
        local_3c[1] = 7;
        local_3c[0] = (*pbVar9 & 7) + param_5;
        if ((int)local_3c[0] < 7) {
          puVar5 = local_3c;
        }
        else {
          puVar5 = local_3c + 1;
        }
        FUN_00488429(iVar7,iVar10,(int)*local_14,*pbVar9 & 0xf8 | *puVar5);
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
    iVar7 = DAT_0058df44 + 8;
    local_c = 0;
    do {
      local_14 = param_4;
      if ((local_c & 1) == 0) {
        if ((DAT_00559de8 <= param_1) && (param_1 < DAT_00559df0)) {
          local_44 = (int)*param_4;
          local_48 = param_2 - local_44;
          if ((int)(&DAT_006552cc)[param_1] <= param_2) {
            local_44 = local_44 - ((param_2 - (&DAT_006552cc)[param_1]) + 1);
          }
          if (local_48 < DAT_00559dec) {
            local_44 = local_44 - (DAT_00559dec - local_48);
            local_48 = DAT_00559dec;
          }
          if (-1 < local_44) {
            (&DAT_006552cc)[param_1] = local_48;
            local_4c = (undefined2 *)(local_1c * local_48 + local_18 + param_1 * 2);
            local_58[1] = 7;
            local_58[0] = (*param_3 & 7) + param_5;
            if ((int)local_58[0] < 7) {
              puVar5 = local_58;
            }
            else {
              puVar5 = local_58 + 1;
            }
            uVar2 = *(undefined2 *)(iVar7 + (*param_3 & 0xf8 | *puVar5) * 2);
            while (-1 < local_44) {
              *local_4c = uVar2;
              local_4c = (undefined2 *)((int)local_4c + DAT_0051c3c0);
              local_44 = local_44 + -1;
            }
          }
        }
        local_14 = param_4 + 1;
        local_10 = 0x1e;
        iVar10 = param_1 + 1;
        pbVar9 = param_3 + 1;
        iVar11 = param_2 + 1;
      }
      else {
        local_10 = 0x20;
        iVar10 = param_1;
        pbVar9 = param_3;
        iVar11 = param_2;
      }
      local_8 = 0;
      piVar3 = &DAT_006552cc + iVar10;
      if (local_10 >> 1 != 0) {
        do {
          if ((DAT_00559de8 <= iVar10) && (iVar10 < DAT_00559df0)) {
            local_5c = (int)*local_14;
            local_60 = iVar11 - local_5c;
            if (*piVar3 <= iVar11) {
              local_5c = local_5c - ((iVar11 - *piVar3) + 1);
            }
            if (local_60 < DAT_00559dec) {
              local_5c = local_5c - (DAT_00559dec - local_60);
              local_60 = DAT_00559dec;
            }
            if (-1 < local_5c) {
              *piVar3 = local_60;
              local_64 = (undefined2 *)(local_1c * local_60 + local_18 + iVar10 * 2);
              local_70[1] = 7;
              local_70[0] = (*pbVar9 & 7) + param_5;
              if ((int)local_70[0] < 7) {
                puVar5 = local_70;
              }
              else {
                puVar5 = local_70 + 1;
              }
              uVar2 = *(undefined2 *)(iVar7 + (*pbVar9 & 0xf8 | *puVar5) * 2);
              while (-1 < local_5c) {
                *local_64 = uVar2;
                local_64 = (undefined2 *)((int)local_64 + DAT_0051c3c0);
                local_5c = local_5c + -1;
              }
            }
          }
          iVar6 = iVar10 + 1;
          piVar4 = piVar3 + 1;
          if ((DAT_00559de8 <= iVar6) && (iVar6 < DAT_00559df0)) {
            local_74 = (int)local_14[1];
            local_78 = iVar11 - local_74;
            if (*piVar4 <= iVar11) {
              local_74 = local_74 - ((iVar11 - *piVar4) + 1);
            }
            if (local_78 < DAT_00559dec) {
              local_74 = local_74 - (DAT_00559dec - local_78);
              local_78 = DAT_00559dec;
            }
            if (-1 < local_74) {
              *piVar4 = local_78;
              local_7c = (undefined2 *)(local_1c * local_78 + local_18 + iVar6 * 2);
              local_88[1] = 7;
              local_88[0] = (pbVar9[1] & 7) + param_5;
              if ((int)local_88[0] < 7) {
                puVar5 = local_88;
              }
              else {
                puVar5 = local_88 + 1;
              }
              uVar2 = *(undefined2 *)(iVar7 + (pbVar9[1] & 0xf8 | *puVar5) * 2);
              while (-1 < local_74) {
                *local_7c = uVar2;
                local_7c = (undefined2 *)((int)local_7c + DAT_0051c3c0);
                local_74 = local_74 + -1;
              }
            }
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 2;
          piVar3 = piVar3 + 2;
          local_14 = local_14 + 2;
          pbVar9 = pbVar9 + 2;
          local_8 = local_8 + 1;
        } while (local_8 < local_10 >> 1);
      }
      if ((local_c & 1) == 0) {
        if ((DAT_00559de8 <= iVar10) && (iVar10 < DAT_00559df0)) {
          iVar6 = (int)*local_14;
          local_8c = iVar11 - iVar6;
          if ((int)(&DAT_006552cc)[iVar10] <= iVar11) {
            iVar6 = iVar6 - ((iVar11 - (&DAT_006552cc)[iVar10]) + 1);
          }
          if (local_8c < DAT_00559dec) {
            iVar6 = iVar6 - (DAT_00559dec - local_8c);
            local_8c = DAT_00559dec;
          }
          if (-1 < iVar6) {
            (&DAT_006552cc)[iVar10] = local_8c;
            local_90 = (undefined2 *)(local_1c * local_8c + local_18 + iVar10 * 2);
            local_9c[1] = 7;
            local_9c[0] = (*pbVar9 & 7) + param_5;
            if ((int)local_9c[0] < 7) {
              puVar5 = local_9c;
            }
            else {
              puVar5 = local_9c + 1;
            }
            uVar2 = *(undefined2 *)(iVar7 + (*pbVar9 & 0xf8 | *puVar5) * 2);
            while (-1 < iVar6) {
              *local_90 = uVar2;
              local_90 = (undefined2 *)((int)local_90 + DAT_0051c3c0);
              iVar6 = iVar6 + -1;
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

