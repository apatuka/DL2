// FUN_004ab834 @ 004ab834 size=2235 sig=undefined FUN_004ab834() cc=unknown
// callers: sprintf,FUN_004ab474,FUN_004aa948,FUN_004aa0a8
// callees: strlen,FUN_004ae0f8,FUN_004ab7d8,FUN_004ab800,FUN_004ab7a8,thunk_FUN_004ae2e4,FUN_004ada10,thunk_FUN_004ae2e4
// strings: \"(null)\"|u\"null)\"

undefined4 FUN_004ab834(undefined4 param_1,undefined4 param_2,char *param_3,uint *param_4)

{
  int iVar1;
  uint *puVar2;
  undefined1 uVar3;
  bool bVar4;
  bool bVar5;
  short sVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  char cVar10;
  int iVar11;
  short *psVar12;
  undefined1 *puVar13;
  char cVar14;
  uint unaff_EBX;
  undefined3 uVar15;
  char *pcVar16;
  char *pcVar17;
  uint uVar18;
  bool bVar19;
  undefined1 local_548 [80];
  undefined4 local_4f8;
  undefined4 local_4f4;
  undefined4 local_4f0;
  undefined4 local_4ec;
  int local_4e8;
  short local_4e4 [512];
  undefined1 local_e4 [2];
  undefined2 local_e2;
  undefined1 local_dc;
  undefined1 local_83 [43];
  int local_58;
  int local_54;
  int local_50;
  short *local_48;
  int local_44;
  int local_40;
  undefined4 local_3c;
  ushort local_36;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  char local_21;
  int local_20;
  short *local_1c;
  char *local_18;
  int local_14;
  char local_d;
  uint local_c;
  uint local_8;
  
  local_4e8 = 0;
  local_4ec = 0;
  local_4f8 = 0;
  local_4f4 = param_1;
  local_4f0 = param_2;
LAB_004ab869:
  pcVar16 = param_3;
  cVar14 = *pcVar16;
  uVar15 = (undefined3)(unaff_EBX >> 8);
  unaff_EBX = CONCAT31(uVar15,cVar14);
  param_3 = pcVar16 + 1;
  if (cVar14 != '\0') {
    if (cVar14 == '%') {
      unaff_EBX = CONCAT31(uVar15,*param_3);
      if (*param_3 != '%') {
        uVar7 = 0;
        local_14 = 0;
        local_d = '\0';
        local_c = 0xffffffff;
        local_8 = 0xffffffff;
        uVar18 = 0;
        bVar19 = false;
        bVar5 = false;
        local_20 = 0;
switchD_004ab90a_default:
        pcVar17 = param_3;
        bVar4 = false;
        cVar14 = *pcVar17;
        uVar15 = (undefined3)(unaff_EBX >> 8);
        unaff_EBX = CONCAT31(uVar15,cVar14);
        param_3 = pcVar17 + 1;
        local_18 = pcVar16;
        if ((cVar14 < ' ') || ('\x7f' < cVar14)) goto switchD_004ab90a_caseD_15;
        switch((&DAT_005207da)[(byte)(cVar14 - 0x20)]) {
        case 0:
          local_18 = pcVar16;
          if (uVar7 != 0) goto switchD_004ab90a_caseD_15;
          if (local_d != '+') {
            local_d = cVar14;
          }
          goto switchD_004ab90a_default;
        case 1:
          local_18 = pcVar16;
          if (uVar7 != 0) goto switchD_004ab90a_caseD_15;
          uVar18 = uVar18 | 1;
          goto switchD_004ab90a_default;
        case 2:
          local_34 = *param_4;
          if (uVar7 < 2) {
            local_8 = local_34;
            if ((int)local_34 < 0) {
              local_8 = -local_34;
              bVar5 = true;
            }
            uVar7 = 3;
            param_4 = param_4 + 1;
          }
          else {
            local_18 = pcVar16;
            if (uVar7 != 4) goto switchD_004ab90a_caseD_15;
            uVar7 = 5;
            param_4 = param_4 + 1;
            local_c = local_34;
          }
          goto switchD_004ab90a_default;
        case 3:
          local_18 = pcVar16;
          if (uVar7 != 0) goto switchD_004ab90a_caseD_15;
          bVar5 = true;
          goto switchD_004ab90a_default;
        case 4:
          local_18 = pcVar16;
          if (3 < uVar7) goto switchD_004ab90a_caseD_15;
          uVar7 = 4;
          local_c = local_c + 1;
          goto switchD_004ab90a_default;
        case 5:
          goto switchD_004ab90a_caseD_5;
        case 6:
          uVar18 = uVar18 | 0x10;
          uVar7 = 5;
          goto switchD_004ab90a_default;
        case 7:
          uVar7 = 5;
          uVar18 = uVar18 & 0xffffffef | 0x100;
          goto switchD_004ab90a_default;
        case 8:
          uVar7 = 5;
          uVar18 = uVar18 & 0xffffffef | 0x200;
          goto switchD_004ab90a_default;
        case 9:
          if (uVar7 == 0) {
            if (!bVar5) {
              bVar19 = true;
              uVar7 = 1;
            }
          }
          else {
switchD_004ab90a_caseD_5:
            cVar14 = cVar14 + -0x30;
            unaff_EBX = CONCAT31(uVar15,cVar14);
            if (uVar7 < 3) {
              uVar7 = 2;
              if (local_8 == 0xffffffff) {
                local_8 = (uint)cVar14;
              }
              else {
                local_8 = local_8 * 10 + (int)cVar14;
              }
            }
            else {
              local_18 = pcVar16;
              if (uVar7 != 4) goto switchD_004ab90a_caseD_15;
              local_c = local_c * 10 + (int)cVar14;
            }
          }
          goto switchD_004ab90a_default;
        case 10:
          goto switchD_004ab90a_caseD_a;
        case 0xb:
          local_3c = 8;
          break;
        case 0xc:
          local_3c = 10;
          break;
        case 0xd:
          local_3c = 0x10;
          local_21 = cVar14 + -0x17;
          break;
        case 0xe:
          local_1c = (short *)*param_4;
          FUN_004ab800(local_1c,local_e4);
          local_dc = 0;
          local_1c = (short *)local_e4;
          param_4 = param_4 + 1;
          goto LAB_004abe95;
        case 0xf:
          uVar8 = 8;
          if ((uVar18 & 0x100) == 0) {
            uVar8 = 6;
          }
          local_1c = (short *)(local_e4 + 1);
          uVar7 = local_c;
          if ((int)local_c < 0) {
            uVar7 = 6;
          }
          thunk_FUN_004ae2e4(param_4,uVar7,local_1c,unaff_EBX,uVar18 & 0xffffff01,uVar8);
          param_4 = (uint *)thunk_FUN_004ae2e4(param_4,uVar18 & 0x100);
          goto LAB_004abe95;
        case 0x10:
          goto switchD_004ab90a_caseD_10;
        case 0x11:
          goto switchD_004ab90a_caseD_11;
        case 0x12:
          if ((uVar18 & 0x210) == 0) {
            uVar18 = uVar18 | 0x10;
          }
switchD_004ab90a_caseD_10:
          if ((uVar18 & 0x10) == 0) {
            local_1c = (short *)local_e4;
            local_e4[1] = 0;
            local_e4[0] = (byte)*param_4;
            local_20 = 0;
            local_44 = 1;
            param_4 = param_4 + 1;
          }
          else {
            local_1c = (short *)local_e4;
            local_e4 = SUB42(*param_4,0);
            local_e2 = 0;
            local_20 = 1;
            local_44 = 1;
            param_4 = param_4 + 1;
          }
          goto LAB_004abf09;
        case 0x13:
          if ((uVar18 & 0x210) == 0) {
            uVar18 = uVar18 | 0x10;
          }
switchD_004ab90a_caseD_11:
          if ((uVar18 & 0x10) == 0) {
            local_1c = (short *)*param_4;
            local_20 = 0;
            if (local_1c == (short *)0x0) {
              local_1c = (short *)s__null__005207c4;
            }
          }
          else {
            local_1c = (short *)*param_4;
            local_20 = 1;
            if (local_1c == (short *)0x0) {
              local_1c = (short *)&DAT_005207cc;
            }
          }
          param_4 = param_4 + 1;
          if (local_20 == 0) {
            uVar7 = local_c;
            if ((int)local_c < 0) {
              uVar7 = 0x7fffffff;
            }
            local_44 = 0;
            for (psVar12 = local_1c; (uVar7 != 0 && ((char)*psVar12 != '\0'));
                psVar12 = (short *)((int)psVar12 + 1)) {
              uVar7 = uVar7 - 1;
              local_44 = local_44 + 1;
            }
          }
          else {
            uVar7 = local_c;
            if ((int)local_c < 0) {
              uVar7 = 0x7fffffff;
            }
            local_44 = 0;
            for (psVar12 = local_1c; (uVar7 != 0 && (*psVar12 != 0)); psVar12 = psVar12 + 1) {
              uVar7 = uVar7 - 1;
              local_44 = local_44 + 1;
            }
          }
          goto LAB_004abf09;
        case 0x14:
          puVar2 = param_4 + 1;
          local_1c = (short *)*param_4;
          param_4 = puVar2;
          if ((uVar18 & 0x10) == 0) {
            if ((uVar18 & 0x200) == 0) {
              *(undefined4 *)local_1c = local_4ec;
            }
            else {
              *local_1c = (short)local_4ec;
            }
          }
          else {
            *(undefined4 *)local_1c = local_4ec;
          }
          goto LAB_004ab869;
        case 0x15:
        case 0x16:
        case 0x17:
          goto switchD_004ab90a_caseD_15;
        case 0x18:
          uVar7 = 5;
          goto switchD_004ab90a_default;
        case 0x19:
          uVar7 = 5;
          goto switchD_004ab90a_default;
        case 0x1a:
          if ((*param_3 == '6') && (pcVar17[2] == '4')) {
            uVar18 = uVar18 & 0xfffffdef | 0x100;
            uVar7 = 5;
            param_3 = pcVar17 + 3;
          }
          else if ((*param_3 == '3') && (pcVar17[2] == '2')) {
            uVar18 = uVar18 & 0xfffffcff | 0x10;
            uVar7 = 5;
            param_3 = pcVar17 + 3;
          }
          else if ((*param_3 == '1') && (pcVar17[2] == '6')) {
            uVar18 = uVar18 & 0xfffffeef | 0x200;
            uVar7 = 5;
            param_3 = pcVar17 + 3;
          }
          else if (*param_3 == '8') {
            uVar18 = uVar18 & 0xfffffcef;
            uVar7 = 5;
            param_3 = pcVar17 + 2;
          }
        default:
          goto switchD_004ab90a_default;
        }
        local_d = '\0';
        cVar10 = '\0';
        goto LAB_004abb85;
      }
      param_3 = pcVar16 + 2;
    }
    if ((((&DAT_0069f56d)[unaff_EBX & 0xff] & 4) != 0) && (*param_3 != '\0')) {
      FUN_004ab7d8(unaff_EBX,local_548);
      unaff_EBX = CONCAT31((int3)(unaff_EBX >> 8),*param_3);
      param_3 = param_3 + 1;
    }
    FUN_004ab7d8(unaff_EBX,local_548);
    goto LAB_004ab869;
  }
  goto LAB_004ac133;
switchD_004ab90a_caseD_a:
  local_3c = 10;
  cVar10 = '\x01';
LAB_004abb85:
  if ((uVar18 & 0x100) == 0) {
    if ((uVar18 & 0x10) == 0) {
      if ((uVar18 & 0x200) == 0) {
        local_34 = *param_4;
        local_2c = local_34;
        if (cVar10 == '\0') {
          local_28 = 0;
          param_4 = param_4 + 1;
        }
        else {
          local_28 = (int)local_34 >> 0x1f;
          param_4 = param_4 + 1;
        }
      }
      else {
        local_36 = (ushort)*param_4;
        if (cVar10 == '\0') {
          local_2c = (uint)local_36;
          local_28 = 0;
          param_4 = param_4 + 1;
        }
        else {
          local_2c = (uint)(short)local_36;
          local_28 = (int)local_2c >> 0x1f;
          param_4 = param_4 + 1;
        }
      }
    }
    else {
      local_30 = *param_4;
      local_2c = local_30;
      if (cVar10 == '\0') {
        local_28 = 0;
        param_4 = param_4 + 1;
      }
      else {
        local_28 = (int)local_30 >> 0x1f;
        param_4 = param_4 + 1;
      }
    }
  }
  else {
    local_2c = *param_4;
    local_28 = param_4[1];
    param_4 = param_4 + 2;
  }
  local_1c = (short *)(local_e4 + 1);
  if ((local_28 == 0) && (local_2c == 0)) {
    if (local_c == 0) {
                    /* WARNING: Ignoring partial resolution of indirect */
      local_e4[1] = 0;
      goto LAB_004abc76;
    }
  }
  else {
    uVar18 = uVar18 | 4;
  }
  FUN_004ae0f8(local_2c,local_28,local_1c,local_3c,cVar10,
               CONCAT31((int3)((uint)local_1c >> 8),local_21));
LAB_004abc76:
  if ((int)local_c < 0) {
LAB_004abe95:
    if ((bVar19) && (0 < (int)local_8)) {
      local_44 = strlen(local_1c);
      if ((char)*local_1c == '-') {
        local_44 = local_44 + -1;
      }
      if (local_44 < (int)local_8) {
        local_14 = local_8 - local_44;
      }
    }
    if (((char)*local_1c == '-') || (local_d != '\0')) {
      if ((char)*local_1c != '-') {
        local_1c = (short *)((int)local_1c + -1);
        *(char *)local_1c = local_d;
      }
      if ((0 < local_14) && ((int)local_c < 0)) {
        local_14 = local_14 + -1;
      }
    }
    local_44 = strlen(local_1c);
  }
  else {
    local_40 = strlen(local_1c);
    local_44 = local_40;
    if ((char)*local_1c == '-') {
      local_40 = local_40 + -1;
    }
    else if (local_d != '\0') {
      local_44 = local_40 + 1;
      local_1c = (short *)((int)local_1c + -1);
      *(char *)local_1c = local_d;
    }
    if (local_40 < (int)local_c) {
      local_14 = local_c - local_40;
    }
  }
LAB_004abf09:
  if ((uVar18 & 5) == 5) {
    if (cVar14 == 'o') {
      if (local_14 < 1) {
        local_14 = 1;
      }
    }
    else if ((cVar14 == 'x') || (cVar14 == 'X')) {
      bVar4 = true;
      local_8 = local_8 - 2;
      local_14 = local_14 + -2;
      if (local_14 < 0) {
        local_14 = 0;
      }
    }
  }
  local_44 = local_44 + local_14;
  if ((!bVar5) && (local_44 < (int)local_8)) {
    do {
      FUN_004ab7d8(0x20,local_548);
      local_8 = local_8 - 1;
    } while (local_44 < (int)local_8);
  }
  if (bVar4) {
    FUN_004ab7d8(0x30,local_548);
    FUN_004ab7d8(unaff_EBX,local_548);
  }
  if (0 < local_14) {
    local_44 = local_44 - local_14;
    local_8 = local_8 - local_14;
    if ((((char)*local_1c == '-') || ((char)*local_1c == ' ')) || ((char)*local_1c == '+')) {
      sVar6 = *local_1c;
      local_1c = (short *)((int)local_1c + 1);
      FUN_004ab7d8((char)sVar6,local_548);
      local_44 = local_44 + -1;
      local_8 = local_8 - 1;
    }
    while (iVar11 = local_14 + -1, bVar19 = local_14 != 0, local_14 = iVar11, bVar19) {
      FUN_004ab7d8(0x30,local_548);
    }
  }
  if (local_20 != 0) {
    iVar11 = 0;
    local_48 = local_1c;
    local_50 = 0;
    local_58 = local_44;
    while (iVar1 = local_58 + -1, bVar19 = 0 < local_58, local_58 = iVar1, bVar19) {
      sVar6 = *local_48;
      local_48 = local_48 + 1;
      local_54 = FUN_004ada10(local_83,CONCAT22((short)((uint)iVar11 >> 0x10),sVar6));
      if (local_54 < 1) break;
      iVar11 = 0;
      puVar9 = local_83;
      puVar13 = (undefined1 *)((int)local_4e4 + local_50);
      if (0 < local_54) {
        do {
          uVar3 = *puVar9;
          unaff_EBX = CONCAT31((int3)(unaff_EBX >> 8),uVar3);
          puVar9 = puVar9 + 1;
          *puVar13 = uVar3;
          puVar13 = puVar13 + 1;
          local_50 = local_50 + 1;
          iVar11 = iVar11 + 1;
        } while (iVar11 < local_54);
      }
    }
    local_1c = local_4e4;
  }
  if (local_44 != 0) {
    local_8 = local_8 - local_44;
    while (local_44 != 0) {
      sVar6 = *local_1c;
      local_44 = local_44 + -1;
      local_1c = (short *)((int)local_1c + 1);
      FUN_004ab7d8((char)sVar6,local_548);
    }
    local_44 = -1;
  }
  while (uVar18 = local_8 - 1, bVar19 = 0 < (int)local_8, local_8 = uVar18, bVar19) {
    FUN_004ab7d8(0x20,local_548);
  }
  goto LAB_004ab869;
switchD_004ab90a_caseD_15:
  while( true ) {
    pcVar16 = local_18 + 1;
    cVar14 = *local_18;
    local_18 = pcVar16;
    if (cVar14 == '\0') break;
    FUN_004ab7d8(cVar14,local_548);
  }
LAB_004ac133:
  FUN_004ab7a8(local_548);
  if (local_4e8 != 0) {
    local_4ec = 0xffffffff;
  }
  return local_4ec;
}

