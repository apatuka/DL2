// FUN_0045b448 @ 0045b448 size=1118 sig=undefined FUN_0045b448() cc=unknown
// callers: 
// callees: FUN_00449fe8,FUN_00476448,FUN_0044ba40,FUN_00475ba4,FUN_0046b0e4,FUN_0043b754,sprintf,FUN_00481a5c,FUN_0045aed4,GetKeyState,FUN_00449ff0,FUN_0042836c,FUN_0043afb0,FUN_00449fd8,DebugMessage,FUN_0044d1a4,FUN_0044c248,FUN_0047ee9c,FUN_0044ba18,FUN_0044c284,FUN_00449cc4,FUN_00449dec
// strings: \"All tasks in this %s are locked. You must unlock some if you want to move a colonist from here.\"|\"You can not drop colonists on this %s while all its tasks are locked.\"|\"This %s already has its maximum number of colonists.  There is no room for any more colonists to work here.\"|\"Oolan's Advice\"|\"You cannot place colonists over empty squares.  Colonists must be put on buildings or construction sites.\"|\"Colonists may only be put on buildings that are inside the settlement.\"|\"You will abandon this territory if you move everyone out of it.\\nAre you sure that you want to leave %s?\"|\"Abandoning Territory\"|\"You can only move colonists into territories you own.\"|\"You must first send a Colonizer here and give it the Build Settlement mission.  Then you can move colonists into this territory.\"|\"You need 25 credits to move each colonist.\"|\"Transfer failed\"|\"%s is full of colonists.  There isn't room for more colonists to move in here.  Either you need to build more Housing or you have reached the territory's population limit.\"|\"For some reason your colonists did not move into this territory.  Please try again.\"

undefined4 FUN_0045b448(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined *puVar8;
  int iVar9;
  undefined1 local_4c8 [1024];
  undefined1 local_c8 [152];
  int local_30;
  int local_2c [3];
  int local_20;
  int local_1c;
  uint local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar5 = DAT_00583d6c;
  iVar4 = DAT_004c5b50;
  iVar9 = DAT_004c5b50 * 0xadc;
  uVar2 = GetKeyState(0x12);
  local_18 = (uint)((uVar2 & 0x8000) != 0);
  iVar3 = FUN_00449cc4(param_1,param_2,&local_8,&local_c);
  if (iVar3 == 0) {
    FUN_0047ee9c(local_8,local_c,&local_10,&local_14);
    if ((((local_10 < 0) || (5 < local_10)) || (local_14 < 0)) || (5 < local_14)) {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Colonists_may_only_be_put_on_bui_005096ac,4,0
                   ,0xb);
    }
    else {
      iVar4 = FUN_0045aed4(local_14 * 6 + local_10);
      if (iVar4 == 0) {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_cannot_place_colonists_over_e_005096a8,
                     4,0,0xb);
      }
      else {
        if ((iVar4 != iVar5) && (*(char *)(iVar4 + 5) != '\x14')) {
          iVar3 = FUN_00475ba4(DAT_00657de0,iVar5,iVar4);
          if (iVar3 == 0) {
            iVar3 = FUN_0044c248(iVar5);
            if (iVar3 == 0) {
              iVar5 = FUN_0044c284(iVar4);
              if (iVar5 == 0) {
                sprintf(local_c8,PTR_s_This__s_already_has_its_maximum_n_005096a4,
                        *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar4 + 4) * 0x32));
              }
              else {
                sprintf(local_c8,PTR_s_You_can_not_drop_colonists_on_th_005097a4,
                        *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar4 + 4) * 0x32));
              }
            }
            else {
              sprintf(local_c8,PTR_s_All_tasks_in_this__s_are_locked__005097a0,
                      *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar5 + 4) * 0x32));
            }
            FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,local_c8,4,0,0xb);
          }
          else if (local_18 != 0) {
            iVar3 = FUN_0044ba40(iVar4);
            local_20 = FUN_0044ba18(iVar4);
            local_20 = iVar3 - local_20;
            local_2c[2] = FUN_0044ba18(iVar5);
            if (local_2c[2] < local_20) {
              piVar7 = local_2c + 2;
            }
            else {
              piVar7 = &local_20;
            }
            local_1c = *piVar7;
            local_2c[1] = 1;
            if (*piVar7 < 2) {
              piVar7 = local_2c + 1;
            }
            else {
              piVar7 = &local_1c;
            }
            local_1c = *piVar7;
            while (iVar3 = local_1c + -1, bVar1 = 0 < local_1c, local_1c = iVar3, bVar1) {
              FUN_00475ba4(DAT_00657de0,iVar5,iVar4);
            }
          }
        }
        FUN_0043afb0();
        FUN_0043b754();
        FUN_00449fe8();
        FUN_00449fd8();
        FUN_00449ff0();
        FUN_00449dec();
      }
    }
  }
  else if (iVar3 == 1) {
    FUN_00481a5c(local_8,local_c,&local_10,&local_14);
    iVar3 = (int)(short)(&DAT_005a0552)[local_14 * 200 + local_10 * 5];
    puVar8 = &DAT_005a43d0 + iVar3 * 0xadc;
    if (local_18 == 0) {
      local_2c[0] = 1;
    }
    else {
      local_2c[0] = FUN_0044ba18(iVar5);
    }
    local_2c[0] = local_2c[0] * 100;
    iVar6 = FUN_0046b0e4(puVar8);
    local_30 = iVar6 - (short)(&DAT_005a4400)[iVar3 * 0x56e];
    if (local_2c[0] < iVar6 - (short)(&DAT_005a4400)[iVar3 * 0x56e]) {
      piVar7 = local_2c;
    }
    else {
      piVar7 = &local_30;
    }
    local_2c[0] = *piVar7;
    if ((short)(&DAT_005a4400)[iVar4 * 0x56e] <= local_2c[0]) {
      sprintf(local_4c8,PTR_s_You_will_abandon_this_territory_i_005096bc,&DAT_005a43d0 + iVar9);
      iVar4 = FUN_0042836c(PTR_s_Abandoning_Territory_005096b8,local_4c8,6,0,0xc);
      if (iVar4 == 2) {
        return 0;
      }
    }
    if ((&DAT_005a43f0)[iVar3 * 0xadc] == (&DAT_005a43f0)[iVar9]) {
      iVar4 = FUN_0044d1a4(puVar8,0x11,0);
      if (iVar4 == -1) {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_must_first_send_a_Colonizer_h_005096c4,
                     4,0,0xb);
      }
      else {
        iVar4 = local_2c[0] + 3;
        if (iVar4 < 0) {
          iVar4 = local_2c[0] + 6;
        }
        if ((int)(&DAT_0059f16c)[(char)(&DAT_005a43f0)[iVar9] * 0xb6] < iVar4 >> 2) {
          FUN_0042836c(PTR_s_Transfer_failed_005096c8,
                       PTR_s_You_need_25_credits_to_move_each_005096cc,4,0,0x11);
        }
        else {
          iVar4 = FUN_0046b0e4(puVar8);
          if ((short)(&DAT_005a4400)[iVar3 * 0x56e] < iVar4) {
            iVar4 = FUN_00476448(&DAT_005a43d0 + iVar9,puVar8,local_2c[0],1,
                                 (int)*(char *)(iVar5 + 7),0xffffffff);
            if (iVar4 == 0) {
              DebugMessage(PTR_s_For_some_reason_your_colonists_d_005096d4);
            }
            else {
              FUN_0043afb0();
              FUN_0043b754();
              FUN_00449fe8();
              FUN_00449fd8();
              FUN_00449ff0();
              FUN_00449dec();
            }
          }
          else {
            sprintf(local_4c8,PTR_s__s_is_full_of_colonists__There_i_005096d0,puVar8);
            FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,local_4c8,4,0,0xb);
          }
        }
      }
    }
    else {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_only_move_colonists_into_005096c0,4,0
                   ,0xb);
    }
  }
  return 1;
}

