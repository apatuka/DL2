// FUN_00485668 @ 00485668 size=3524 sig=undefined FUN_00485668() cc=unknown
// callers: WinMain
// callees: FUN_0044de9c,FUN_004851ec,ReLinkArmy,SyncCreateBuilding,FUN_00423690,SpyCaught,GetBuildingTasks,FUN_0048558c,FUN_004237d0,FUN_00484fa0,FUN_0046c9d8,FUN_0044d1a4,FUN_00485264,FUN_00416e70,FUN_00445f08,FUN_0047ca98,FUN_004855d4,SearchForSubs,FUN_00485584,_DeleteBuilding,FUN_00441bf4,FUN_00483d58,FUN_0046e56c,memset,FUN_004667ac,FUN_00416e20,FUN_00485364,CheckDiscovery,FUN_0048514c,FUN_00485344,FUN_0044d1e4,FUN_004853f4,DeleteUnit
// strings: \"DETECT_MINE_MISSION1\"|\"DETECT_MINE_MISSION2\"|\"SABOTAGE_MISSION\"|\"Sabotage Destroys Building?\"|\"Sabotage\"|\"sabotaged\"|\"Shaman\"|\"spied\"|\"StealTechM\"|\"stole tech\"|\"SUBVERT_MISSION\"|\" subverted\"|\"POISON_LAND_MISSION\"|\"poisoned\"|\"KW of energy\"|\"stole resources\"

void FUN_00485668(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  int *piVar9;
  int local_24c [13];
  undefined1 local_218 [448];
  undefined **local_58;
  undefined **local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(local_218,0,0x1c0);
  local_10 = 0;
  piVar9 = &DAT_005904dc;
  do {
    iVar8 = *piVar9;
    iVar6 = iVar8 * 0x5c;
    puVar7 = &DAT_00645370 + iVar8 * 0x2e;
    local_14 = (int)(char)(&DAT_0059f162)[(char)(&DAT_00645378)[iVar6] * 0x2d8];
    if (((&DAT_00645376)[iVar6] != '\0') &&
       (iVar2 = FUN_00416e70(puVar7,(int)(char)(&DAT_00645395)[iVar6],local_14), iVar2 != 0)) {
      iVar2 = (&DAT_006453ac)[iVar8 * 0x17];
      if (param_1 == 1) {
        switch((&DAT_00645395)[iVar6]) {
        case 6:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (*(char *)(iVar2 + 0x20) != -1)) &&
             ((iVar8 = SpyCaught(iVar2,puVar7,4), iVar8 == 0 &&
              (uVar4 = FUN_0046c9d8(100,s_SABOTAGE_MISSION_00512436),
              uVar4 < *(short *)(&DAT_0064539a + iVar6) * 0x19 + 0x32U)))) {
            local_24 = FUN_0048558c(iVar2);
            if (local_24 == 0) {
              local_28 = FUN_004855d4(iVar2);
              if (local_28 != 0) {
                FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x16,&DAT_0064537b + iVar6,
                             *(undefined4 *)(&DAT_004f9dbc + *(char *)(local_28 + 4) * 0x32),iVar2,0
                             ,(int)*(char *)(iVar2 + 0x20),0);
                FUN_004237d0((int)*(char *)(iVar2 + 0x20),0x17,iVar2,
                             *(undefined4 *)(&DAT_004f9dbc + *(char *)(local_28 + 4) * 0x32),0,0,
                             (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
                FUN_0044de9c(&DAT_0059f160 + *(char *)(iVar2 + 0x20) * 0x2d8,
                             (int)*(char *)(local_28 + 4),(int)*(char *)(iVar2 + 0x21),local_24c);
                uVar4 = FUN_0046c9d8(100,s_Sabotage_Destroys_Building__00512447);
                if (uVar4 < 0x1e) {
                  _DeleteBuilding(&DAT_005a43d0 + *(short *)(local_28 + 8) * 0xadc,
                                  (int)*(char *)(local_28 + 7));
                }
                else {
                  do {
                    local_30 = *(short *)(local_28 + 0x14) + 0x32;
                    if (local_24c[0] < local_30) {
                      piVar5 = local_24c;
                    }
                    else {
                      piVar5 = &local_30;
                    }
                    local_2c = *piVar5;
                    *(undefined2 *)(local_28 + 0x14) = (undefined2)local_2c;
                    GetBuildingTasks(&DAT_0059f160 + *(char *)(iVar2 + 0x20) * 0x2d8,local_28);
                  } while ((*(short *)(local_28 + 0x14) < local_24c[0]) &&
                          (uVar4 = FUN_0046c9d8(100,s_Sabotage_00512463), uVar4 < 0x19));
                }
              }
            }
            else if (*(char *)(local_24 + 7) == '\t') {
              FUN_00423690((int)*(char *)(iVar2 + 0x20),0x18,iVar2,0,0,0);
              FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x19,iVar2,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(char *)(iVar2 + 0x20) * 0x2d8]],0,0,
                           (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
              *(undefined1 *)(local_24 + 8) = (&DAT_00645378)[iVar6];
              ReLinkArmy(local_24,iVar2,iVar2 + 0x76,iVar2 + 0x7a);
            }
            else {
              FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x16,&DAT_0064537b + iVar6,
                           local_24 + 0xb,iVar2,0,(int)*(char *)(iVar2 + 0x20),0);
              FUN_004237d0((int)*(char *)(iVar2 + 0x20),0x17,iVar2,local_24 + 0xb,0,0,
                           (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
              DeleteUnit(local_24);
            }
            FUN_00485584(puVar7,s_sabotaged_0051246c);
            FUN_004851ec(puVar7);
          }
          break;
        case 0xb:
          if ((&DAT_0064539c)[iVar8 * 0x2e] != 0) {
            (&DAT_0064539c)[iVar8 * 0x2e] = 0;
            FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1c,&DAT_0064537b + iVar6,0,0,0);
          }
          (&DAT_00645395)[iVar6] = 0;
          break;
        case 0xc:
          FUN_00485364((int)(char)(&DAT_00645378)[iVar6],iVar2);
          break;
        case 0xe:
          if (99 < *(short *)(&DAT_00645398 + iVar6)) {
            (&DAT_00645395)[iVar6] = 0;
          }
          break;
        case 0x10:
          iVar8 = FUN_00485264((int)(char)(&DAT_00645378)[iVar6],iVar2);
          if (iVar8 != 0) {
            (&DAT_00645395)[iVar6] = 0;
          }
          break;
        case 0x11:
          SearchForSubs((int)(char)(&DAT_00645378)[iVar6],iVar2);
          break;
        case 0x13:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (iVar8 = SpyCaught(iVar2,puVar7,4), iVar8 == 0)) && (*(int *)(iVar2 + 0x8a8) != 0)) {
            uVar4 = FUN_0046c9d8(100,s_DETECT_MINE_MISSION1_0051240c);
            if (uVar4 < (uint)(int)(short)(&DAT_0055a164)
                                          [(char)(&DAT_0059f162)
                                                 [(char)(&DAT_00645378)[iVar6] * 0x2d8]]) {
              FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x96,&DAT_0064537b + iVar6,iVar2,0,0,
                           (int)*(short *)(iVar2 + 0x1a),0);
              DeleteUnit(puVar7);
            }
            else {
              local_1c = (int)(short)(&DAT_0055a172)
                                     [(char)(&DAT_0059f162)[(char)(&DAT_00645378)[iVar6] * 0x2d8]];
              uVar4 = FUN_0046c9d8(100,s_DETECT_MINE_MISSION2_00512421);
              if (uVar4 < (uint)(*(short *)(&DAT_0064539a + iVar6) * 10 + local_1c)) {
                FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x95,iVar2,&DAT_0064537b + iVar6,0,0,
                             (int)*(short *)(iVar2 + 0x1a),0);
                local_20 = 0;
                do {
                  if ((1 << ((byte)local_20 & 0x1f) & *(uint *)(iVar2 + 0x8a8)) != 0) {
                    FUN_004237d0(local_20,0x97,iVar2,
                                 (&PTR_s_ChCh_t_00509038)
                                 [(char)(&DAT_0059f162)[(char)(&DAT_00645378)[iVar6] * 0x2d8]],0,0,
                                 (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
                  }
                  local_20 = local_20 + 1;
                } while (local_20 < 7);
                *(undefined4 *)(iVar2 + 0x8a8) = 0;
              }
            }
          }
          break;
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
          local_8 = -1;
          local_c = (char)(&DAT_00645395)[iVar6] + -0x14;
          iVar3 = 0;
          local_54 = (undefined **)&DAT_0059f161;
          do {
            if ((*(char *)local_54 != '\0') &&
               (iVar1 = iVar3, *(char *)((int)local_54 + 1) == local_c)) break;
            iVar3 = iVar3 + 1;
            local_54 = local_54 + 0xb6;
            iVar1 = local_8;
          } while (iVar3 < 7);
          local_8 = iVar1;
          if (local_8 != -1) {
            if (((*(char *)(iVar2 + 0x20) == -1) || (*(char *)(iVar2 + 0x20) == local_8)) &&
               (((&DAT_004faf8d)[(char)(&DAT_00645376)[iVar6] * 0x24] != '\x01' ||
                (*(char *)(iVar2 + 0x21) != '\0')))) {
              local_18 = 0;
              local_54 = (undefined **)(&DAT_006453b8 + iVar8 * 0x17);
              local_58 = &PTR_s_ChCh_t_00509038 + local_c;
              do {
                if ((*local_54 != (undefined *)0x0) && ((&DAT_00645377)[iVar6] == '\x04')) {
                  FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1d,*local_54 + 0xb,*local_58,0,0)
                  ;
                  FUN_004237d0(local_8,0x1f,*local_58,*local_54 + 0xb,0,0,
                               (int)(char)(&DAT_00645378)[iVar6],0);
                  (*local_54)[8] = (undefined1)local_8;
                }
                local_18 = local_18 + 1;
                local_54 = local_54 + 1;
              } while (local_18 < 3);
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1d,&DAT_0064537b + iVar6,
                           (&PTR_s_ChCh_t_00509038)[local_c],0,0);
              FUN_004237d0(local_8,0x1f,(&PTR_s_ChCh_t_00509038)[local_c],&DAT_0064537b + iVar6,0,0,
                           (int)(char)(&DAT_00645378)[iVar6],0);
              (&DAT_00645378)[iVar6] = (undefined1)local_8;
              (&DAT_00645395)[iVar6] = 0;
              if (*(char *)(iVar2 + 0x20) == local_8) {
                ReLinkArmy(puVar7,iVar2,iVar2 + 0x7a,iVar2 + 0x76);
              }
              if ((&DAT_00645376)[iVar6] == '\f') {
                local_58 = (undefined **)(&DAT_006453b8 + iVar8 * 0x17);
                iVar8 = 0;
                local_54 = &PTR_s_ChCh_t_00509038 + local_c;
                do {
                  if (*local_58 != (undefined *)0x0) {
                    FUN_00423690((int)(char)(*local_58)[8],0x1d,*local_58 + 0xb,*local_54,0,0);
                    FUN_004237d0(local_8,0x1f,*local_54,*local_58 + 0xb,0,0,
                                 (int)(char)(*local_58)[8],0);
                    (*local_58)[8] = (undefined1)local_8;
                    (*local_58)[0x25] = 0;
                  }
                  iVar8 = iVar8 + 1;
                  local_58 = local_58 + 1;
                } while (iVar8 < 3);
              }
            }
            else {
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1e,&DAT_0064537b + iVar6,
                           (&PTR_s_ChCh_t_00509038)[local_c],(&PTR_s_ChCh_t_00509038)[local_c],0);
            }
          }
        }
      }
      else {
        switch((&DAT_00645395)[iVar6]) {
        case 1:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (*(char *)(iVar2 + 0x20) != -1)) && (iVar8 = SpyCaught(iVar2,puVar7,1), iVar8 == 0)) {
            FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],7,&DAT_0064537b + iVar6,iVar2,0,0,
                         (int)*(char *)(iVar2 + 0x20),0);
            FUN_004851ec(puVar7);
            FUN_00485584(puVar7,s_spied_0051247d);
          }
          break;
        case 2:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (*(char *)(iVar2 + 0x20) != -1)) &&
             ((iVar8 = SpyCaught(iVar2,puVar7,2), iVar8 == 0 &&
              (uVar4 = FUN_0046c9d8(100,s_SUBVERT_MISSION_00512499),
              uVar4 < *(short *)(&DAT_0064539a + iVar6) * 0x19 + 0x32U)))) {
            local_3c = FUN_00484fa0(puVar7,local_218 + *(short *)(iVar2 + 0x1a) * 4);
            if (0 < local_3c) {
              FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0xf,&DAT_0064537b + iVar6,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(char *)(iVar2 + 0x20) * 0x2d8]],iVar2,0,
                           (int)*(char *)(iVar2 + 0x20),0);
              FUN_004237d0((int)*(char *)(iVar2 + 0x20),0x10,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[(char)(&DAT_00645378)[iVar6] * 0x2d8]],iVar2,0,0,
                           (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
              local_40 = *(char *)(iVar2 + 0x27) - local_3c;
              local_44 = 0;
              if (local_40 < 0) {
                piVar5 = &local_44;
              }
              else {
                piVar5 = &local_40;
              }
              *(char *)(iVar2 + 0x27) = (char)*piVar5;
            }
            FUN_004851ec(puVar7);
            FUN_00485584(puVar7,s_subverted_005124a9);
          }
          break;
        case 3:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (*(char *)(iVar2 + 0x20) != -1)) &&
             ((iVar8 = SpyCaught(iVar2,puVar7,4), iVar8 == 0 &&
              (uVar4 = FUN_0046c9d8(100,s_POISON_LAND_MISSION_005124b4),
              uVar4 < *(short *)(&DAT_0064539a + iVar6) * 0x19 + 0x32U)))) {
            FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x13,&DAT_0064537b + iVar6,iVar2,0,0,
                         (int)*(char *)(iVar2 + 0x20),0);
            FUN_004237d0((int)*(char *)(iVar2 + 0x20),0x12,
                         (&PTR_s_ChCh_t_00509038)
                         [(char)(&DAT_0059f162)[(char)(&DAT_00645378)[iVar6] * 0x2d8]],iVar2,0,0,
                         (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
            FUN_0047ca98(3,iVar2,2);
            FUN_004851ec(puVar7);
            FUN_00485584(puVar7,s_poisoned_005124c8);
          }
          break;
        case 4:
          if (((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
              (*(char *)(iVar2 + 0x20) != -1)) && (iVar8 = SpyCaught(iVar2,puVar7,2), iVar8 == 0)) {
            uVar4 = FUN_0046c9d8(100,s_StealTechM_00512483);
            if (uVar4 < (uint)(int)*(short *)(&DAT_0055a0bc + local_14 * 2)) {
              local_38 = FUN_0048514c((int)(char)(&DAT_00645378)[iVar6],(int)*(char *)(iVar2 + 0x20)
                                     );
              if (local_38 == 0) {
                FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0xc,&DAT_0064537b + iVar6,iVar2,
                             (&PTR_s_ChCh_t_00509038)
                             [(char)(&DAT_0059f162)[*(char *)(iVar2 + 0x20) * 0x2d8]],0,
                             (int)*(char *)(iVar2 + 0x20),0);
              }
              else {
                FUN_00483d58((int)(char)(&DAT_00645378)[iVar6],&DAT_004fbbac + local_38 * 0x19);
                FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0xb,&DAT_0064537b + iVar6,
                             *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + local_38 * 0x32),
                             (&PTR_s_ChCh_t_00509038)
                             [(char)(&DAT_0059f162)[*(char *)(iVar2 + 0x20) * 0x2d8]],iVar2,
                             (int)*(char *)(iVar2 + 0x20),0);
              }
              FUN_00485584(puVar7,s_stole_tech_0051248e);
            }
            FUN_004851ec(puVar7);
          }
          break;
        case 5:
          if ((*(char *)(iVar2 + 0x20) != (&DAT_00645378)[iVar6]) &&
             (iVar8 = SpyCaught(iVar2,puVar7,4), iVar8 == 0)) {
            local_48 = 0;
            local_4c = 0;
            local_50 = FUN_004853f4((int)(char)(&DAT_00645378)[iVar6],iVar2);
            if (local_50 != -1) {
              iVar8 = 1;
              local_54 = (undefined **)(iVar2 + 0x3e);
              do {
                if (local_48 < (int)*local_54) {
                  local_48 = (int)*local_54 * 3;
                  if (local_48 < 0) {
                    local_48 = local_48 + 3;
                  }
                  local_48 = local_48 >> 2;
                  local_4c = iVar8;
                }
                iVar8 = iVar8 + 1;
                local_54 = local_54 + 1;
              } while (iVar8 < 0xb);
              if (local_4c != 0) {
                piVar5 = (int *)(iVar2 + 0x3a + local_4c * 4);
                *piVar5 = *piVar5 - (int)(short)local_48;
                *(int *)(&DAT_005a440a + local_4c * 4 + local_50 * 0xadc) =
                     *(int *)(&DAT_005a440a + local_4c * 4 + local_50 * 0xadc) +
                     (int)(short)local_48;
                FUN_004237d0((int)(char)(&DAT_00645378)[iVar6],0x14,&DAT_0064537b + iVar6,local_48,
                             (&PTR_s_credits_005090f0)[local_4c],iVar2,(int)*(char *)(iVar2 + 0x20),
                             0);
                FUN_004237d0((int)*(char *)(iVar2 + 0x20),0x15,local_48,
                             (&PTR_s_credits_005090f0)[local_4c],iVar2,0,
                             (int)(char)(&DAT_00645378)[iVar6],(int)*(short *)(iVar2 + 0x1a));
                FUN_004851ec(puVar7);
                FUN_00485584(puVar7,s_stole_resources_005124d1);
              }
            }
          }
          break;
        case 7:
          uVar4 = FUN_0046c9d8(100,s_Shaman_00512476);
          if (uVar4 < (uint)(int)*(short *)(&DAT_0055a11e + local_14 * 2)) {
            local_34 = FUN_0046c9d8(5,s_Shaman_00512476);
            iVar8 = FUN_004667ac(iVar2,*(undefined4 *)(&DAT_004dca4c + local_34 * 4));
            if (iVar8 != 0) {
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x11,&DAT_0064537b + iVar6,
                           (&PTR_s_credits_00509098)[*(int *)(&DAT_004dca4c + local_34 * 4)],iVar2,0
                          );
            }
          }
          break;
        case 8:
          iVar8 = FUN_00441bf4(iVar2);
          if ((iVar8 != 0) &&
             ((*(char *)(iVar2 + 0x20) == (&DAT_00645378)[iVar6] || (*(char *)(iVar2 + 0x20) == -1))
             )) {
            if ((&DAT_00645378)[iVar6] != *(char *)(iVar2 + 0x20)) {
              FUN_0046e56c(iVar2,(int)(char)(&DAT_00645378)[iVar6]);
            }
            iVar8 = FUN_0044d1e4(iVar2,0x11,0);
            if (iVar8 == -1) {
              CheckDiscovery(iVar2,(int)(char)(&DAT_00645378)[iVar6],
                             (int)(char)(&DAT_00645376)[iVar6]);
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1a,iVar2,0,0,0);
              SyncCreateBuilding(iVar2,1);
              *(undefined2 *)(iVar2 + 0x30) = 100;
              DeleteUnit(puVar7);
            }
            else {
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1b,iVar2,0,0,0);
              FUN_00445f08(puVar7);
            }
          }
          break;
        case 9:
          if (((*(char *)(iVar2 + 0x21) == '\0') && (*(int *)(iVar2 + 0x8ac) != 0)) &&
             ((*(char *)(iVar2 + 0x20) == (&DAT_00645378)[iVar6] || (*(char *)(iVar2 + 0x20) == -1))
             )) {
            if ((&DAT_00645378)[iVar6] != *(char *)(iVar2 + 0x20)) {
              FUN_0046e56c(iVar2,(int)(char)(&DAT_00645378)[iVar6]);
            }
            iVar8 = FUN_0044d1a4(iVar2,0x14,0);
            if (iVar8 == -1) {
              CheckDiscovery(iVar2,(int)(char)(&DAT_00645378)[iVar6],0x1e);
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1a,iVar2,0,0,0);
              SyncCreateBuilding(iVar2,0x26);
              *(undefined2 *)(iVar2 + 0x30) = 100;
              DeleteUnit(puVar7);
            }
            else {
              FUN_00423690((int)(char)(&DAT_00645378)[iVar6],0x1b,iVar2,0,0,0);
              FUN_00445f08(puVar7);
            }
          }
          break;
        case 0x12:
          iVar8 = FUN_00416e20(puVar7);
          if ((iVar8 != 0) &&
             (iVar8 = FUN_00485344((int)(char)(&DAT_00645378)[iVar6],iVar2), iVar8 != 0)) {
            DeleteUnit(puVar7);
          }
        }
      }
    }
    local_10 = local_10 + 1;
    piVar9 = piVar9 + 1;
    if (0x22f < local_10) {
      return;
    }
  } while( true );
}

