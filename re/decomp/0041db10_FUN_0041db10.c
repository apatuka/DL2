// FUN_0041db10 @ 0041db10 size=1428 sig=undefined FUN_0041db10() cc=unknown
// callers: 
// callees: sprintf,FUN_00449cc4,FUN_0045c704,FUN_004761b0,FUN_0041c378,GetKeyState,FUN_004762a8,FUN_0041daa4,MoveLaborToHousing,FUN_0044eb4c,FUN_0044c754,FUN_0044ba18,FUN_0042836c,FUN_0044c8ac,FUN_0041bc1c,FUN_0044ba40,FUN_0041c418,FUN_0044b7d8,FUN_00459068,FUN_0041c3dc,FUN_0041b908,FUN_0041c36c
// strings: \"This %s already has its maximum number of colonists.  There is no room for any more colonists to work here.\"|\"Oolan's Advice\"|\"The housing pool is full.\"|\"You can not drag colonists to a locked task.\"|\"You may only drag colonists to Task Buttons, the Labor Pool, the Housing Pool, and the Satellite Map. Try again.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041db10(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 local_e4 [5];
  undefined1 local_d0 [152];
  undefined4 local_38 [5];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  int local_10;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar1 = GetKeyState(0x12);
  local_14 = (uint)((uVar1 & 0x8000) != 0);
  iVar2 = FUN_00449cc4(param_1,param_2,local_8,local_c);
  if ((iVar2 < 0xc) && (7 < iVar2)) {
    iVar2 = _DAT_0053b340 + 1;
  }
  FUN_00459068();
  if (iVar2 != DAT_0053b868) {
    iVar7 = iVar2 + -2;
    local_10 = DAT_0053b868 + -2;
    if (iVar2 == 1) {
      DAT_00583d70 = (int)*(short *)(DAT_0053b84c + 0x1a);
      FUN_0045c704(param_1,param_2);
      if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
        FUN_0041c3dc();
        FUN_0041c418();
      }
      FUN_0041b908();
      iVar2 = DAT_0053b850;
      if (local_10 < 6) {
        iVar7 = FUN_0044ba40(DAT_0053b850);
        FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                [(char)(&DAT_005a43f0)[*(short *)(iVar2 + 8) * 0xadc] * 0x2d8],
                     *(undefined4 *)(iVar2 + 0x14 + local_10 * 4),
                     iVar7 - *(int *)(DAT_0053b850 + 0x14 + local_10 * 4));
      }
      else {
        iVar2 = FUN_0044b7d8(DAT_0053b84c);
        iVar7 = FUN_0044c754(DAT_0053b84c);
        iVar2 = iVar2 - iVar7;
        uVar8 = FUN_0044c754(DAT_0053b84c);
        FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8
                                ],uVar8,iVar2);
      }
      iVar2 = 0;
      puVar9 = (undefined4 *)(DAT_0053b850 + 0x18);
      puVar3 = local_38;
      do {
        *puVar3 = *puVar9;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 1;
        puVar9 = puVar9 + 1;
      } while (iVar2 < 5);
      FUN_004761b0(DAT_0053b84c,DAT_0053b850,local_38,
                   CONCAT31((int3)((uint)puVar9 >> 8),*(undefined1 *)(DAT_0053b84c + 0x9ae)));
      FUN_004762a8(DAT_0053b84c,DAT_0053b850);
    }
    else if (iVar2 - 2U < 6) {
      if (local_14 == 0) {
        local_18 = FUN_0041daa4();
      }
      else if (DAT_0053b868 == 7) {
        local_18 = FUN_0044c754(DAT_0053b84c);
      }
      else {
        local_18 = *(int *)(DAT_0053b850 + 0x18 + local_10 * 4);
      }
      if (iVar2 == 7) {
        local_1c = FUN_0044c754(DAT_0053b84c);
        iVar4 = FUN_0044b7d8(DAT_0053b84c);
      }
      else {
        local_1c = *(int *)(DAT_0053b850 + 0x18 + iVar7 * 4);
        iVar4 = FUN_0044ba40(DAT_0053b850);
        iVar5 = FUN_0044ba18(DAT_0053b850);
        if ((iVar4 == iVar5) && (DAT_0053b868 == 7)) {
          sprintf(local_d0,PTR_s_This__s_already_has_its_maximum_n_005096a4,
                  *(undefined4 *)(&DAT_004f9dbc + *(char *)(DAT_0053b850 + 4) * 0x32));
          FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,local_d0,4,0,0xb);
          local_18 = 0;
        }
      }
      if ((((local_1c < iVar4) && (0 < local_18)) &&
          ((0x100 << ((byte)iVar7 & 0x1f) & (int)*(short *)(DAT_0053b850 + 2)) == 0)) &&
         ((DAT_0053b868 == 7 ||
          ((0x100 << ((byte)local_10 & 0x1f) & (int)*(short *)(DAT_0053b850 + 2)) == 0)))) {
        local_20 = local_18;
        local_24 = 0;
        iVar4 = 0;
        piVar6 = (int *)(DAT_0053b850 + 0x18);
        do {
          iVar5 = *piVar6;
          piVar6 = piVar6 + 1;
          local_24 = local_24 + iVar5;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 5);
        do {
          if (DAT_0053b868 == 7) {
            FUN_0044c8ac(DAT_0053b84c,DAT_0053b850,iVar7);
            local_24 = local_24 + 1;
          }
          else if (iVar2 == 7) {
            iVar4 = MoveLaborToHousing(DAT_0053b84c,DAT_0053b850,local_10);
            if (iVar4 == 0) {
              if (local_18 == local_20) {
                FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_The_housing_pool_is_full__00509790,
                             4,0,0xb);
              }
              local_18 = 1;
            }
          }
          else {
            piVar6 = (int *)(DAT_0053b850 + 0x18 + iVar7 * 4);
            *piVar6 = *piVar6 + 1;
            piVar6 = (int *)(DAT_0053b850 + 0x18 + local_10 * 4);
            *piVar6 = *piVar6 + -1;
          }
          local_18 = local_18 + -1;
        } while ((local_18 != 0) &&
                ((DAT_0053b868 != 7 || (iVar4 = FUN_0044ba40(DAT_0053b850), local_24 < iVar4))));
        FUN_0044eb4c(PTR_DAT_004d5988,DAT_0053b84c,_DAT_0053b848,&DAT_0053b854,0);
        if (*(char *)(DAT_0053b850 + 0x30) != '\0') {
          FUN_0041c3dc();
          FUN_0041c418();
        }
        FUN_0041b908();
        iVar2 = DAT_0053b850;
        if (_DAT_0053b340 < 6) {
          iVar7 = FUN_0044ba40(DAT_0053b850);
          FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                  [(char)(&DAT_005a43f0)[*(short *)(iVar2 + 8) * 0xadc] * 0x2d8],
                       *(undefined4 *)(iVar2 + 0x14 + _DAT_0053b340 * 4),
                       iVar7 - *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4));
        }
        else {
          iVar2 = FUN_0044b7d8(DAT_0053b84c);
          iVar7 = FUN_0044c754(DAT_0053b84c);
          iVar2 = iVar2 - iVar7;
          uVar8 = FUN_0044c754(DAT_0053b84c);
          FUN_0041bc1c((int)(char)(&DAT_0059f162)
                                  [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] *
                                   0x2d8],uVar8,iVar2);
        }
        iVar2 = 0;
        puVar9 = (undefined4 *)(DAT_0053b850 + 0x18);
        puVar3 = local_e4;
        do {
          *puVar3 = *puVar9;
          iVar2 = iVar2 + 1;
          puVar3 = puVar3 + 1;
          puVar9 = puVar9 + 1;
        } while (iVar2 < 5);
        FUN_004761b0(DAT_0053b84c,DAT_0053b850,local_e4,
                     CONCAT31((int3)((uint)puVar3 >> 8),*(undefined1 *)(DAT_0053b84c + 0x9ae)));
        FUN_004762a8(DAT_0053b84c,DAT_0053b850);
        FUN_0041c378();
        FUN_0041c36c();
      }
      else if ((0x100 << ((byte)iVar7 & 0x1f) & (int)*(short *)(DAT_0053b850 + 2)) != 0) {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_not_drag_colonists_to_a_l_0050978c,
                     4,0,0xb);
      }
    }
    else {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_only_drag_colonists_to_T_00509788,4,0
                   ,0xb);
    }
  }
  return 1;
}

