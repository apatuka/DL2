// FUN_0045c704 @ 0045c704 size=821 sig=undefined FUN_0045c704() cc=unknown
// callers: FUN_00421178,FUN_0041db10
// callees: FUN_00476448,FUN_0043edd8,FUN_0046b0e4,FUN_00428824,FUN_00482f94,sprintf,FUN_00481a5c,FUN_0042836c,DebugMessage,FUN_0044d1a4,FUN_00459ea8,FUN_00449cc4,FUN_00449dec
// strings: \"You will abandon this territory if you move everyone out of it.\\nAre you sure that you want to leave %s?\"|\"Abandoning Territory\"|\"You can only move colonists into territories you own.\"|\"Oolan's Advice\"|\"You must first send a Colonizer here and give it the Build Settlement mission.  Then you can move colonists into this territory.\"|\"You need 25 credits to move each colonist.\"|\"Transfer failed\"|\"%s is full of colonists.  There isn't room for more colonists to move in here.  Either you need to build more Housing or you have reached the territory's population limit.\"|\"For some reason your colonists did not move into this territory.  Please try again.\"

undefined4 FUN_0045c704(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined2 uVar5;
  undefined *puVar6;
  int iVar7;
  undefined1 local_120 [256];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_00583d70 != 0) &&
     ((iVar1 = FUN_00449cc4(param_1,param_2,&local_8,&local_c), iVar1 == 0 || (iVar1 == 1)))) {
    if (iVar1 == 0) {
      if (DAT_004d5ad0 == 0) {
        FUN_00459ea8(local_8,local_c,&local_10,&local_14);
      }
      else {
        FUN_0043edd8(local_8,local_c,&local_10,&local_14);
      }
    }
    else {
      FUN_00481a5c(local_8,local_c,&local_10,&local_14);
    }
    iVar1 = DAT_00583d70;
    if ((((-1 < local_10) && (local_10 < DAT_004d5b1a)) && (-1 < local_14)) &&
       (local_14 < DAT_004d5b1b)) {
      iVar2 = (int)(short)(&DAT_005a0552)[local_14 * 200 + local_10 * 5];
      if (iVar2 != DAT_00583d70) {
        iVar7 = DAT_00583d70 * 0xadc;
        puVar6 = &DAT_005a43d0 + iVar2 * 0xadc;
        if ((short)(&DAT_005a4400)[DAT_00583d70 * 0x56e] < 200) {
          local_18 = -1;
        }
        else {
          local_18 = FUN_00428824(0xb,(int)(short)(&DAT_005a4400)[DAT_00583d70 * 0x56e],0x19);
        }
        if (local_18 == 0) {
          FUN_00449dec();
          return 1;
        }
        if ((local_18 == -1) || ((short)(&DAT_005a4400)[iVar1 * 0x56e] < 100)) {
          local_18 = (int)(short)(&DAT_005a4400)[iVar1 * 0x56e];
        }
        else {
          local_18 = local_18 * 100;
        }
        iVar3 = FUN_0046b0e4(puVar6);
        local_1c = iVar3 - (short)(&DAT_005a4400)[iVar2 * 0x56e];
        if (local_18 < iVar3 - (short)(&DAT_005a4400)[iVar2 * 0x56e]) {
          piVar4 = &local_18;
        }
        else {
          piVar4 = &local_1c;
        }
        local_18 = *piVar4;
        if ((short)(&DAT_005a4400)[iVar1 * 0x56e] <= local_18) {
          sprintf(local_120,PTR_s_You_will_abandon_this_territory_i_005096bc,&DAT_005a43d0 + iVar7);
          iVar1 = FUN_0042836c(PTR_s_Abandoning_Territory_005096b8,local_120,6,0,0xc);
          if (iVar1 == 2) {
            FUN_00449dec();
            return 1;
          }
        }
        if ((&DAT_005a43f0)[iVar2 * 0xadc] == (&DAT_005a43f0)[iVar7]) {
          iVar1 = FUN_0044d1a4(puVar6,0x11,0);
          if (iVar1 == -1) {
            FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,
                         PTR_s_You_must_first_send_a_Colonizer_h_005096c4,4,0,0xb);
          }
          else {
            iVar1 = local_18 + 3;
            if (iVar1 < 0) {
              iVar1 = local_18 + 6;
            }
            if ((int)(&DAT_0059f16c)[(char)(&DAT_005a43f0)[iVar7] * 0xb6] < iVar1 >> 2) {
              FUN_0042836c(PTR_s_Transfer_failed_005096c8,
                           PTR_s_You_need_25_credits_to_move_each_005096cc,4,0,0x11);
            }
            else {
              iVar1 = FUN_0046b0e4(puVar6);
              if ((short)(&DAT_005a4400)[iVar2 * 0x56e] < iVar1) {
                iVar1 = FUN_0046b0e4(puVar6);
                local_20 = iVar1 - (short)(&DAT_005a4400)[iVar2 * 0x56e];
                if (local_18 < iVar1 - (short)(&DAT_005a4400)[iVar2 * 0x56e]) {
                  piVar4 = &local_18;
                }
                else {
                  piVar4 = &local_20;
                }
                local_18 = *piVar4;
                uVar5 = (undefined2)((uint)local_18 >> 0x10);
                if (DAT_004d59b4 == 5) {
                  iVar2 = CONCAT22((short)((uint)piVar4 >> 0x10),DAT_0053b848);
                  iVar1 = CONCAT22(uVar5,DAT_0053b340) + -1;
                }
                else {
                  iVar2 = CONCAT22(uVar5,0xffff);
                  iVar1 = iVar2;
                }
                iVar1 = FUN_00476448(&DAT_005a43d0 + iVar7,puVar6,local_18,1,iVar2,iVar1);
                if (iVar1 == 0) {
                  DebugMessage(PTR_s_For_some_reason_your_colonists_d_005096d4);
                }
              }
              else {
                sprintf(local_120,PTR_s__s_is_full_of_colonists__There_i_005096d0,puVar6);
                FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,local_120,4,0,0xb);
              }
            }
          }
        }
        else {
          FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_only_move_colonists_into_005096c0
                       ,4,0,0xb);
        }
        FUN_00482f94(PTR_DAT_004d5988);
      }
      FUN_00449dec();
    }
  }
  DAT_00583d70 = 0;
  return 1;
}

