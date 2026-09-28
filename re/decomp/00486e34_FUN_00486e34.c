// FUN_00486e34 @ 00486e34 size=2446 sig=undefined FUN_00486e34() cc=unknown
// callers: WinMain
// callees: FUN_00486b74,FUN_00486d30,FUN_00423690,FUN_0044fe58,FUN_0044fdf0,FUN_004412d4,FUN_004a68dc,memset,FUN_00450340,FUN_00450094,FUN_00450320,FUN_00486964,sprintf,FUN_00450204,FUN_00450380,FUN_0044ffbc,FUN_0044fe1c,FUN_004500d8
// strings: \"%d turns\"

void FUN_00486e34(void)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  int *piVar10;
  char *pcVar11;
  int *piVar12;
  char *pcVar13;
  int local_160;
  int local_15c;
  int local_154;
  undefined4 local_14c;
  undefined2 local_148;
  undefined1 local_146;
  char local_144 [4];
  char local_140 [4];
  char local_13c;
  int local_138;
  int *local_134;
  short *local_130;
  short *local_12c;
  char local_128 [256];
  char local_28 [12];
  char local_1c [12];
  
  local_160 = 0;
  local_15c = 0;
  DAT_0065e428 = 0;
  bVar3 = false;
  memset(&DAT_0065e43a,0,0xe);
  local_154 = 0;
  local_128[0] = '\0';
  if ((DAT_0058f1ec == 0) && (1 < DAT_004d5aec)) {
    FUN_00486964();
    iVar8 = 0;
    piVar12 = &DAT_0065e3b0;
    pcVar9 = &DAT_0059f161;
    do {
      if ((*pcVar9 == '\0') || (*piVar12 == 0)) {
        FUN_00486d30(iVar8);
      }
      else if (((iVar8 == DAT_0058f1f4) && ((code *)PTR_FUN_004d02b8 != FUN_00457ac0)) &&
              ((DAT_0059f154 < 0 || (0xe < DAT_0059f154)))) {
        FUN_00423690(iVar8,0x87,0,0,0,0);
        FUN_00486b74(iVar8);
      }
      else if ((iVar8 == DAT_0058f1f4) && (iVar4 = FUN_0044ffbc(), iVar4 != 0)) {
        if (DAT_004d5a94 == 0xe) {
          FUN_00423690(iVar8,0x88,0,0,0,0);
        }
        else if (DAT_004d5a94 == 0x1b) {
          FUN_00423690(iVar8,0x89,0,0,0,0);
        }
        else if (DAT_004d5a94 == 0x23) {
          FUN_00423690(iVar8,0x8a,0,0,0,0);
        }
        FUN_00486b74(iVar8);
      }
      else {
        local_160 = local_160 + 1;
        local_15c = iVar8;
      }
      iVar8 = iVar8 + 1;
      piVar12 = piVar12 + 1;
      pcVar9 = pcVar9 + 0x2d8;
    } while (iVar8 < 7);
    iVar8 = 0;
    piVar10 = &DAT_0065e404;
    local_12c = &DAT_0065e43a;
    local_130 = &DAT_0065e42c;
    local_134 = &DAT_0065e3e8;
    piVar12 = &DAT_0065e3cc;
    pcVar9 = &DAT_0059f161;
    do {
      bVar2 = true;
      iVar4 = FUN_0044fe1c(5);
      if ((iVar4 != 0) && ('\x02' < *pcVar9)) {
        bVar2 = false;
      }
      if ((bVar2) &&
         ((((DAT_004d5b00 == '\0' && (DAT_0065e424 <= *piVar12)) && (local_154 <= *piVar12)) ||
          ((DAT_004d5b00 == '\x02' && (DAT_004d5af8 <= *local_134)))))) {
        if (*local_130 == 0) {
          if ((DAT_004d5b00 == '\x02') && (*piVar10 < DAT_004d5afc)) {
            *piVar10 = *piVar10 + 1;
          }
          if ((DAT_004d5b00 == '\0') ||
             ((DAT_004d5b00 == '\x02' && (DAT_004d5afc + -1 <= *piVar10)))) {
            iVar4 = FUN_0044fe1c(0xc);
            if ((iVar4 != 0) && (iVar8 == DAT_0058f1f4)) {
              FUN_0044fe58(0xc);
              FUN_00423690(DAT_0058f1f4,0x8f,0,0,0,0);
              return;
            }
            if ((iVar8 != DAT_0058f1f4) || (iVar4 = FUN_00450094(), iVar4 != 0)) {
              *local_130 = 1;
            }
            if ((DAT_004d5a94 == 0x2a) && (iVar4 = FUN_00450204(2), iVar4 == 0)) {
              *local_130 = 0;
            }
          }
          else if (DAT_004d5b00 == '\x02') {
            if (*piVar10 == 1) {
              if (iVar8 == DAT_0058f1f4) {
                FUN_00423690(DAT_0058f1f4,0x86,0,0,0,0);
              }
              else {
                iVar4 = FUN_004412d4(DAT_0058f1f4,iVar8,0x10);
                if (iVar4 == 0) {
                  FUN_00423690(DAT_0058f1f4,0x85,(&PTR_s_ChCh_t_00509038)[pcVar9[1]],0,0,0);
                }
              }
            }
            else if (*piVar10 < DAT_004d5afc) {
              local_14c = DAT_005126a8;
              local_148 = DAT_005126ac;
              local_146 = DAT_005126ae;
              local_144[0] = s__d_turns_005126af[0];
              local_144[1] = s__d_turns_005126af[1];
              local_144[2] = s__d_turns_005126af[2];
              local_144[3] = s__d_turns_005126af[3];
              local_140[0] = s__d_turns_005126af[4];
              local_140[1] = s__d_turns_005126af[5];
              local_140[2] = s__d_turns_005126af[6];
              local_140[3] = s__d_turns_005126af[7];
              local_13c = s__d_turns_005126af[8];
              local_138 = *piVar10;
              if (*piVar10 == 1) {
                uVar6 = 0xffffffff;
                pcVar11 = (char *)&local_14c;
                do {
                  pcVar13 = pcVar11;
                  if (uVar6 == 0) break;
                  uVar6 = uVar6 - 1;
                  pcVar13 = pcVar11 + 1;
                  cVar1 = *pcVar11;
                  pcVar11 = pcVar13;
                } while (cVar1 != '\0');
                uVar6 = ~uVar6;
                pcVar11 = pcVar13 + -uVar6;
                pcVar13 = local_28;
                for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
                  pcVar11 = pcVar11 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *pcVar13 = *pcVar11;
                  pcVar11 = pcVar11 + 1;
                  pcVar13 = pcVar13 + 1;
                }
              }
              else {
                sprintf(local_28,local_144,*piVar10);
              }
              if (DAT_004d5afc - local_138 == 1) {
                uVar6 = 0xffffffff;
                pcVar11 = (char *)&local_14c;
                do {
                  pcVar13 = pcVar11;
                  if (uVar6 == 0) break;
                  uVar6 = uVar6 - 1;
                  pcVar13 = pcVar11 + 1;
                  cVar1 = *pcVar11;
                  pcVar11 = pcVar13;
                } while (cVar1 != '\0');
                uVar6 = ~uVar6;
                pcVar11 = pcVar13 + -uVar6;
                pcVar13 = local_28 + 0xc;
                for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
                  pcVar11 = pcVar11 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *pcVar13 = *pcVar11;
                  pcVar11 = pcVar11 + 1;
                  pcVar13 = pcVar13 + 1;
                }
              }
              else {
                sprintf(local_28 + 0xc,local_144,DAT_004d5afc - local_138);
              }
              if (iVar8 == DAT_0058f1f4) {
                FUN_00423690(DAT_0058f1f4,0x91,local_28,local_28 + 0xc,0,0);
              }
              else {
                iVar4 = FUN_004412d4(iVar8,DAT_0058f1f4,0x10);
                if (iVar4 == 0) {
                  FUN_00423690(DAT_0058f1f4,0x92,(&PTR_s_ChCh_t_00509038)[pcVar9[1]],local_28 + 0xc,
                               0,0);
                }
              }
            }
          }
        }
        else {
          if (DAT_0065e428 == 0) {
            uVar6 = 0xffffffff;
            pcVar11 = (&PTR_s_ChCh_t_00509038)[pcVar9[1]];
            do {
              pcVar13 = pcVar11;
              if (uVar6 == 0) break;
              uVar6 = uVar6 - 1;
              pcVar13 = pcVar11 + 1;
              cVar1 = *pcVar11;
              pcVar11 = pcVar13;
            } while (cVar1 != '\0');
            uVar6 = ~uVar6;
            pcVar11 = pcVar13 + -uVar6;
            pcVar13 = local_128;
            for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
              pcVar11 = pcVar11 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
              *pcVar13 = *pcVar11;
              pcVar11 = pcVar11 + 1;
              pcVar13 = pcVar13 + 1;
            }
          }
          else {
            FUN_004a68dc(local_128,&DAT_005126b8);
            FUN_004a68dc(local_128,(&PTR_s_ChCh_t_00509038)[pcVar9[1]]);
          }
          DAT_0065e428 = DAT_0065e428 + 1;
          *local_12c = 1;
        }
        local_154 = *piVar12;
      }
      else {
        *piVar10 = 0;
        *local_130 = 0;
      }
      iVar8 = iVar8 + 1;
      piVar10 = piVar10 + 1;
      local_12c = local_12c + 1;
      local_130 = local_130 + 1;
      local_134 = local_134 + 1;
      piVar12 = piVar12 + 1;
      pcVar9 = pcVar9 + 0x2d8;
    } while (iVar8 < 7);
    if (((DAT_004d5b00 == '\x02') && (DAT_0065e420 < DAT_004d5af8)) &&
       (iVar8 = FUN_00450320(), iVar8 == 0)) {
      iVar8 = 0;
      pcVar9 = &DAT_0059f161;
      do {
        if (*pcVar9 != '\0') {
          FUN_00423690(iVar8,0x82,DAT_004d5af8,0,0,0);
        }
        iVar8 = iVar8 + 1;
        pcVar9 = pcVar9 + 0x2d8;
      } while (iVar8 < 7);
    }
    else {
      if ((1 < local_160) && (DAT_004d5af4 != 0)) {
        iVar8 = 0;
        pcVar9 = &DAT_0059f161;
        do {
          iVar4 = iVar8;
          if (*pcVar9 != '\0') break;
          iVar8 = iVar8 + 1;
          pcVar9 = pcVar9 + 0x2d8;
          iVar4 = -1;
        } while (iVar8 < 7);
        iVar8 = 0;
        pcVar9 = &DAT_0059f161;
LAB_0048744a:
        if ((iVar4 < 0) || (6 < iVar8)) goto LAB_00487453;
        if ((*pcVar9 == '\0') || (iVar4 == iVar8)) {
LAB_00487443:
          iVar8 = iVar8 + 1;
          pcVar9 = pcVar9 + 0x2d8;
          goto LAB_0048744a;
        }
        iVar5 = FUN_004412d4(iVar8,iVar4,0x10);
        if (iVar5 != 0) {
          bVar3 = true;
          goto LAB_00487443;
        }
        bVar3 = false;
LAB_00487453:
        if (bVar3) {
          DAT_0065e428 = 1;
          iVar8 = 0;
          local_12c = &DAT_0065e43a;
          pcVar9 = &DAT_0059f161;
          do {
            if (*pcVar9 != '\0') {
              *local_12c = 1;
            }
            local_12c = local_12c + 1;
            iVar8 = iVar8 + 1;
            pcVar9 = pcVar9 + 0x2d8;
          } while (iVar8 < 7);
        }
        if ((!bVar3) || ((DAT_004d5b00 == '\0' && (DAT_0065e428 == 1)))) {
          uVar6 = 0;
          iVar8 = 0;
          local_12c = &DAT_0065e43a;
          do {
            if (*local_12c != 0) {
              iVar4 = 0;
              do {
                iVar5 = FUN_004412d4(iVar8,iVar4,0x10);
                if (iVar5 != 0) {
                  uVar6 = uVar6 | 1 << ((byte)iVar4 & 0x1f);
                }
                iVar4 = iVar4 + 1;
              } while (iVar4 < 7);
            }
            iVar8 = iVar8 + 1;
            local_12c = local_12c + 1;
          } while (iVar8 < 7);
          local_12c = &DAT_0065e43a;
          iVar8 = 0;
          do {
            if ((1 << ((byte)iVar8 & 0x1f) & uVar6) != 0) {
              *local_12c = 1;
            }
            iVar8 = iVar8 + 1;
            local_12c = local_12c + 1;
          } while (iVar8 < 7);
        }
      }
      if ((local_160 == 1) && (iVar8 = FUN_00450320(), iVar8 == 0)) {
        if ((DAT_004d5a94 != 7) || (iVar8 = FUN_00450204(2), iVar8 != 0)) {
          DAT_0065e428 = 1;
        }
        (&DAT_0065e43a)[local_15c] = 1;
      }
      else {
        iVar8 = FUN_00450380();
        if (iVar8 != 0) {
          DAT_0065e428 = 1;
          (&DAT_0065e43a)[DAT_0058f1f4] = 1;
        }
      }
      if (DAT_0065e428 != 0) {
        iVar8 = FUN_004500d8();
        if (iVar8 == 0) {
          if ((DAT_004d5a94 == 0xd) || (DAT_004d5a94 == 0xf)) {
            iVar8 = FUN_0044fdf0(8);
            iVar8 = iVar8 * 0x44 + DAT_004d5a94 * 0xd8;
            FUN_00423690(DAT_0058f1f4,0x8c,*(undefined4 *)(&DAT_004c61ac + iVar8),
                         (&PTR_s_credits_00509098)[*(int *)(&DAT_004c61a8 + iVar8)],0,0);
          }
          else if (DAT_004d5a94 == 0x1b) {
            FUN_00423690(DAT_0058f1f4,0x8d,0,0,0,0);
          }
        }
        else if ((DAT_0065e428 == 1) || (DAT_004d5b00 == '\x02')) {
          DAT_0065e3ac = 1;
          if ((&DAT_0065e43a)[DAT_0058f1f4] == 0) {
            if ((&DAT_0059f161)[DAT_0058f1f4 * 0x2d8] != '\0') {
              if (DAT_004d5b00 == '\x02') {
                FUN_00423690(DAT_0058f1f4,0x83,local_128,0,0,0);
              }
              else {
                FUN_00423690(DAT_0058f1f4,0x7e,local_128,DAT_0065e424,0,0);
              }
            }
          }
          else if (bVar3) {
            local_12c = (short *)&DAT_0059f162;
            iVar8 = 0;
            do {
              if ((iVar8 != DAT_0058f1f4) &&
                 (iVar4 = FUN_004412d4(DAT_0058f1f4,iVar8,0x10), iVar4 != 0)) {
                FUN_00423690(DAT_0058f1f4,0x81,(&PTR_s_ChCh_t_00509038)[(char)*local_12c],0,0,0);
              }
              iVar8 = iVar8 + 1;
              local_12c = (short *)((int)local_12c + 0x2d8);
            } while (iVar8 < 7);
          }
          else if ((DAT_004d5b00 == '\x02') && (iVar8 = FUN_00450340(), iVar8 == 0)) {
            FUN_00423690(DAT_0058f1f4,0x84,0,0,0,0);
          }
          else {
            FUN_00423690(DAT_0058f1f4,0x7f,0,0,0,0);
          }
        }
        else {
          DAT_0065e424 = local_154 + 1;
          if ((&DAT_0059f161)[DAT_0058f1f4 * 0x2d8] != '\0') {
            FUN_00423690(DAT_0058f1f4,0x80,local_128,DAT_0065e424,0,0);
          }
        }
      }
    }
  }
  return;
}

