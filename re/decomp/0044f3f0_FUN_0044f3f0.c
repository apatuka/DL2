// FUN_0044f3f0 @ 0044f3f0 size=2183 sig=undefined FUN_0044f3f0() cc=unknown
// callers: FUN_0044fcd4,FUN_0046ab18,FUN_004045d0
// callees: GetBuildingTasks,FUN_0044bea8,FUN_0046c9d8,IsBuildTaskDifferent,FUN_00486964,FUN_0044cce4,FUN_0044ba18,ProduceUnits,FUN_0046b0e4,FUN_0044c718,FUN_00472974,FUN_00423690,memset,MoveLaborToHousingNoNet,FUN_0044eb4c,FUN_0044d7b4,FUN_0044c49c,FUN_004412d4,FUN_0047dfdc,FUN_0044f2fc,CanUpgradeBuilding,FUN_004237d0,FUN_0044f1e8

void FUN_0044f3f0(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int local_b8 [6];
  uint local_a0 [5];
  undefined1 local_8c [4];
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_74;
  int local_6c;
  int local_68;
  int local_64;
  int *local_60;
  uint *local_5c;
  undefined1 *local_58;
  int *local_54;
  undefined1 local_50 [4];
  int local_4c;
  int local_48;
  int local_44 [3];
  int local_38;
  int local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  local_24 = 0;
  local_28 = 0;
  local_2c = 0;
  piVar7 = &DAT_004c5ee8;
  piVar5 = local_b8;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    *piVar5 = *piVar7;
    piVar7 = piVar7 + 1;
    piVar5 = piVar5 + 1;
  }
  local_8 = &DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8;
  if (param_2 != 0) {
    FUN_0044bea8(param_1);
  }
  memset(local_8c,0,0x2c);
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_20 = 0;
  local_1c = 0;
  local_c = 0;
  local_54 = (int *)(param_1 + 0x154);
  do {
    iVar6 = *local_54;
    if ((((iVar6 != 0) && (*(char *)(iVar6 + 4) != '\0')) && ((*(byte *)(iVar6 + 2) & 4) != 0)) &&
       ((*(byte *)(iVar6 + 2) & 2) != 0)) {
      local_30 = FUN_0044ba18(iVar6);
      FUN_0044eb4c(local_8,param_1,local_c,local_a0,0);
      local_34 = 0;
      local_5c = local_a0;
      local_58 = (undefined1 *)(iVar6 + 0x2c);
      piVar7 = (int *)(iVar6 + 0x18);
      do {
        switch(*local_58) {
        case 2:
          if ((param_2 != 0) && (param_3 == 1)) {
            *(short *)(iVar6 + 0x14) = *(short *)(iVar6 + 0x14) - (short)*local_5c;
            local_44[1] = 0;
            local_44[0] = (int)*(short *)(iVar6 + 0x14);
            if (*(short *)(iVar6 + 0x14) < 1) {
              piVar5 = local_44 + 1;
            }
            else {
              piVar5 = local_44;
            }
            iVar3 = *piVar5;
            *(short *)(iVar6 + 0x14) = (short)iVar3;
            if ((short)iVar3 == 0) {
              GetBuildingTasks(local_8,iVar6);
              if ((char)local_8[1] < '\x03') {
                FUN_0044c49c(iVar6,local_30);
              }
              else {
                memset(iVar6 + 0x18,0,0x14);
                if (*(char *)(iVar6 + 0x2d) == '\0') {
                  *(undefined4 *)(iVar6 + 0x18) = local_30;
                }
                else {
                  *(undefined4 *)(iVar6 + 0x1c) = local_30;
                }
              }
              if ((DAT_004d5b00 == '\0') && (*(char *)(iVar6 + 4) == '%')) {
                FUN_00486964();
                if (*(char *)(param_1 + 0x20) == DAT_0058f1f4) {
                  FUN_00423690(DAT_0058f1f4,0x43,param_1,0,0,0);
                }
                else {
                  iVar3 = FUN_004412d4(DAT_0058f1f4,(int)*(char *)(param_1 + 0x20),0x10);
                  if (iVar3 == 0) {
                    FUN_004237d0(DAT_0058f1f4,0x41,
                                 (&PTR_s_ChCh_t_00509038)
                                 [(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8]],0,0,0,
                                 (int)*(char *)(param_1 + 0x20),0);
                  }
                  else {
                    FUN_004237d0(DAT_0058f1f4,0x42,
                                 (&PTR_s_ChCh_t_00509038)
                                 [(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8]],0,0,0,
                                 (int)*(char *)(param_1 + 0x20),0);
                  }
                }
              }
              else if ((*(byte *)(iVar6 + 2) & 0x40) == 0) {
                FUN_00423690((int)*(char *)(param_1 + 0x20),0x3e,
                             *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar6 + 4) * 0x32),param_1,0,
                             0);
                *(ushort *)(iVar6 + 2) = *(ushort *)(iVar6 + 2) | 0x40;
                if ((*(char *)(iVar6 + 5) == '\x05') &&
                   ((&DAT_0059f19e)[*(char *)(param_1 + 0x20) * 0x2d8] == '\0')) {
                  FUN_00423690((int)*(char *)(param_1 + 0x20),0x37,0,0,0,0);
                }
              }
              else {
                FUN_00423690((int)*(char *)(param_1 + 0x20),0x3f,
                             *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar6 + 4) * 0x32),param_1,0,
                             0);
              }
            }
            else if ((0x100 << ((byte)local_34 & 0x1f) & (int)*(short *)(iVar6 + 2)) == 0) {
              local_60 = piVar7;
              do {
                iVar3 = *local_60;
                if ((iVar3 == 0) ||
                   (iVar3 = IsBuildTaskDifferent(iVar6,local_34,iVar3,iVar3 + -1), iVar3 != 0))
                break;
                iVar3 = MoveLaborToHousingNoNet(param_1,iVar6,local_34);
              } while (iVar3 != 0);
            }
          }
          break;
        case 3:
          if (param_3 == 1) {
            local_7c = local_7c + (short)*local_5c;
          }
          break;
        case 4:
          if (param_3 == 1) {
            local_74 = local_74 + (short)*local_5c;
          }
          break;
        case 5:
          if (param_3 == 1) {
            local_10 = local_10 + (short)*local_5c;
          }
          break;
        case 6:
          if (param_3 == 1) {
            local_6c = local_6c + (short)*local_5c;
          }
          break;
        case 7:
          if (param_3 == 1) {
            local_14 = local_14 + (short)*local_5c;
          }
          break;
        case 8:
          if (((param_2 != 0) && (param_3 == 1)) &&
             (uVar2 = FUN_0046c9d8(100,&DAT_004c618d), uVar2 < *local_5c)) {
            local_64 = local_64 + 1;
            FUN_00423690((int)*(char *)(param_1 + 0x20),0x3d,param_1,0,0,0);
          }
          break;
        case 9:
          if (param_3 == 2) {
            local_1c = local_1c + *local_5c;
          }
          break;
        case 10:
          if (param_3 == 2) {
            local_20 = local_20 + *local_5c;
          }
          break;
        case 0xb:
          if (param_3 == 1) {
            local_b8[*(int *)(&DAT_004f9de6 + *(char *)(iVar6 + 4) * 0x32)] =
                 local_b8[*(int *)(&DAT_004f9de6 + *(char *)(iVar6 + 4) * 0x32)] + *local_5c;
          }
          break;
        case 0xc:
          if (param_3 == 1) {
            local_88 = local_88 + (short)*local_5c;
          }
          break;
        case 0xd:
          if (param_3 == 1) {
            local_80 = local_80 + (short)*local_5c;
          }
          break;
        case 0xe:
          if (param_3 == 1) {
            local_18 = local_18 + (short)*local_5c;
          }
          break;
        case 0xf:
          if (param_3 == 1) {
            local_84 = local_84 + (short)*local_5c;
          }
          break;
        case 0x10:
          if (param_3 == 1) {
            local_68 = local_68 + (short)*local_5c;
          }
          break;
        case 0x11:
          if (param_3 == 1) {
            local_24 = local_24 + (short)*local_5c;
          }
          break;
        case 0x12:
          if (param_3 == 1) {
            local_28 = local_28 + (short)*local_5c;
          }
          break;
        case 0x13:
          if (param_3 == 1) {
            local_2c = local_2c + (short)*local_5c;
          }
          break;
        case 0x15:
          if (((param_2 != 0) && (param_3 == 1)) && (iVar3 = FUN_0044c718(iVar6), iVar3 != -1)) {
            *(short *)(iVar6 + 0x16) = *(short *)(iVar6 + 0x16) + (short)*local_5c;
            iVar3 = FUN_0044c718(iVar6);
            if (iVar3 <= *(short *)(iVar6 + 0x16)) {
              if (((&DAT_004f9dc5)[*(char *)(iVar6 + 4) * 0x32] == '\x02') &&
                 ((&DAT_004f9df7)[*(char *)(iVar6 + 4) * 0x32] == '\x01')) {
                local_38 = (int)*(char *)(iVar6 + 7) % 6;
                local_44[2] = (int)*(char *)(iVar6 + 7) / 6;
                FUN_0044cce4(param_1,local_38,local_44[2],2);
                uVar1 = FUN_0044f1e8(param_1,iVar6);
                *(undefined1 *)(iVar6 + 7) = uVar1;
                FUN_0044d7b4(param_1,iVar6,(int)*(char *)(iVar6 + 7),1);
              }
              FUN_00423690((int)*(char *)(param_1 + 0x20),0x4b,
                           *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar6 + 4) * 0x32),param_1,
                           *(undefined4 *)
                            ((int)&PTR_s_Housing_004f9dee + *(char *)(iVar6 + 4) * 0x32),0);
              *(char *)(iVar6 + 4) = *(char *)(iVar6 + 4) + '\x01';
              *(undefined2 *)(iVar6 + 0x16) = 0;
              GetBuildingTasks(local_8,iVar6);
              FUN_0044bea8(param_1);
              iVar3 = CanUpgradeBuilding(iVar6);
              if (iVar3 == 0) {
                uVar4 = FUN_0044ba18(iVar6);
                FUN_0044c49c(iVar6,uVar4);
              }
              FUN_0047dfdc(param_1);
            }
            if ((0x100 << ((byte)local_34 & 0x1f) & (int)*(short *)(iVar6 + 2)) == 0) {
              local_60 = piVar7;
              while ((iVar3 = *local_60, iVar3 != 0 &&
                     (iVar3 = IsBuildTaskDifferent(iVar6,local_34,iVar3,iVar3 + -1), iVar3 == 0))) {
                *local_60 = *local_60 + -1;
                iVar3 = FUN_0044ba18(iVar6);
                FUN_0044c49c(iVar6,iVar3 + 1);
              }
            }
          }
        }
        local_34 = local_34 + 1;
        piVar7 = piVar7 + 1;
        local_5c = local_5c + 1;
        local_58 = local_58 + 1;
      } while (local_34 < 5);
    }
    local_c = local_c + 1;
    local_54 = local_54 + 0xd;
    if (0x23 < local_c) {
      if (param_2 == 0) {
        local_c = 1;
        piVar7 = (int *)(param_1 + 0xaae);
        local_54 = &local_88;
        do {
          *piVar7 = *piVar7 + (int)(short)*local_54;
          local_c = local_c + 1;
          piVar7 = piVar7 + 1;
          local_54 = local_54 + 1;
        } while (local_c < 0xb);
        *(int *)(param_1 + 0xaba) = *(int *)(param_1 + 0xaba) - (int)(short)local_1c;
        *(int *)(param_1 + 0xabe) = *(int *)(param_1 + 0xabe) + (int)(short)local_1c;
        *(int *)(param_1 + 0xac2) = *(int *)(param_1 + 0xac2) - (int)(short)local_20;
        *(int *)(param_1 + 0xac6) = *(int *)(param_1 + 0xac6) + (int)(short)local_20;
      }
      else {
        iVar6 = 1;
        piVar7 = local_b8;
        do {
          piVar7 = piVar7 + 1;
          if (*piVar7 != 0) {
            ProduceUnits(param_1,iVar6,*piVar7);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 6);
        *(int *)(local_8 + 0xc) = *(int *)(local_8 + 0xc) + local_18;
        *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) + (short)local_24;
        local_48 = FUN_0046b0e4(param_1);
        local_4c = (int)*(short *)(param_1 + 0x30);
        if (*(short *)(param_1 + 0x30) < local_48) {
          piVar7 = &local_4c;
        }
        else {
          piVar7 = &local_48;
        }
        *(short *)(param_1 + 0x30) = (short)*piVar7;
        FUN_0044f2fc(param_1,local_28);
        *(short *)(param_1 + 0x9b2) = *(short *)(param_1 + 0x9b2) + (short)local_2c;
        piVar7 = &local_88;
        *(short *)(local_8 + 0x40) = *(short *)(local_8 + 0x40) + (short)local_10;
        local_c = 1;
        local_54 = (int *)(param_1 + 0x3e);
        do {
          *local_54 = *local_54 + (int)(short)*piVar7;
          local_c = local_c + 1;
          local_54 = local_54 + 1;
          piVar7 = piVar7 + 1;
        } while (local_c < 0xb);
        if (param_3 == 2) {
          if (*(int *)(param_1 + 0x4a) < local_1c) {
            FUN_00472974(param_1,(int)*(char *)(param_1 + 0x20),4,
                         local_1c - *(int *)(param_1 + 0x4a),1,local_50,local_50);
          }
          if (*(int *)(param_1 + 0x52) < local_20) {
            FUN_00472974(param_1,(int)*(char *)(param_1 + 0x20),6,
                         local_20 - *(int *)(param_1 + 0x52),1,local_50,local_50);
          }
          piVar7 = (int *)(param_1 + 0x4a);
          if (local_1c < *piVar7) {
            piVar7 = &local_1c;
          }
          local_1c = *piVar7;
          piVar5 = (int *)(param_1 + 0x52);
          if (local_20 < *piVar5) {
            piVar5 = &local_20;
          }
          iVar6 = *piVar5;
          local_1c._0_2_ = (short)*piVar7;
          *(int *)(param_1 + 0x4a) = *(int *)(param_1 + 0x4a) - (int)(short)local_1c;
          *(int *)(param_1 + 0x4e) = *(int *)(param_1 + 0x4e) + (int)(short)local_1c;
          local_20._0_2_ = (short)iVar6;
          *(int *)(param_1 + 0x52) = *(int *)(param_1 + 0x52) - (int)(short)local_20;
          *(int *)(param_1 + 0x56) = *(int *)(param_1 + 0x56) + (int)(short)local_20;
        }
      }
      if (param_3 == 1) {
        *(undefined2 *)(param_1 + 0x2a) = (undefined2)local_18;
        *(undefined2 *)(param_1 + 0x2c) = (undefined2)local_14;
        *(short *)(param_1 + 0x2e) = (short)local_10;
      }
      return;
    }
  } while( true );
}

