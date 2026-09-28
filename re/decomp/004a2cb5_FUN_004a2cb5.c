// FUN_004a2cb5 @ 004a2cb5 size=1400 sig=undefined FUN_004a2cb5() cc=unknown
// callers: FUN_0043be98,FUN_00427440,FUN_004393e8,FUN_0041f544,FUN_0041e81c,FUN_0042f04c,CheckSubInfo,FUN_00428a50,UserMessageObject__CheckMessage,FUN_0041665c,CheckSubUnit,CheckSubTech,FUN_004219bc,FUN_0043baf4,FUN_00439e98,FUN_00415514,CheckColonyAssistant,FUN_0042c328,FUN_0042623c,FUN_00424590,FUN_00413eb4,CheckUnitList,FUN_0042f5d8,CheckBuildingList,FUN_00413784,FUN_00414870,FUN_0042bc50,FUN_00427da0,FUN_00423f44,FUN_0042ebb8,FUN_0043044c,CheckMoveStuff,FUN_00426ab0,CheckTechDet,FUN_0043632c,FUN_0042d304,CheckEventLog,FUN_00436ef4,FUN_0042e7ec,CheckViewCombat,CheckBuilding,FUN_0042e080,FUN_00436864,CheckTechTree,CheckSubRes,FUN_0041585c,FUN_00416474,FUN_004169e8,CheckArmy,CheckExitSave,FUN_0042ac68,FUN_00437668,FUN_004a32d7
// callees: FUN_0049f31e,FUN_0049f715,FUN_0048e385,FUN_004a240f,FUN_0048e319,FUN_004960fd,FUN_004a228a,FUN_004a2a27,FUN_0048e169,FUN_004a2847,FUN_004a26e8,FUN_004a2962,FUN_0049f4c2,FUN_0048e3f1,FUN_004a2be7,FUN_004a29cb,FUN_00494d38,FUN_004a2498,FUN_004a2238,FUN_0049eb44,FUN_004a2c32,FUN_0048c434,FUN_0049f696,FUN_0048e1d5,FUN_004a2376,FUN_0048e241,FUN_0049551a

bool FUN_004a2cb5(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int local_2c;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  FUN_004960fd();
  FUN_00494d38();
  if (((param_1 == 0) || (iVar1 = FUN_0049551a(DAT_0051e384,param_1), iVar1 == -1)) ||
     ((*(byte *)(param_1 + 0x1c) & 0x88) != 0)) {
    return false;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    local_14 = DAT_0051bddc;
    FUN_0048c434(*(undefined4 *)(param_1 + 0x3c));
  }
  if (*(int *)(param_1 + 100) == 0) {
    *(undefined4 *)(param_1 + 0x80) = 0;
    *(undefined4 *)(param_1 + 0x78) = 0;
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(undefined4 *)(param_1 + 0x7c) = 0;
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x94) = 0;
    iVar1 = FUN_0049f715(param_1);
    if (iVar1 == 0) {
      FUN_0049f696(**(undefined4 **)(param_1 + 300));
    }
    *(undefined4 *)(param_1 + 100) = 1;
  }
  FUN_004a26e8(param_1);
  FUN_0048e3f1(&local_8,&local_c);
  if (*(int *)(param_1 + 0x68) == 0) {
    uVar2 = FUN_0049f4c2(param_1,local_8,local_c,param_1 + 0x84,0,0);
    *(undefined4 *)(param_1 + 0x7c) = uVar2;
  }
  else {
    iVar1 = FUN_004a2a27(*(undefined4 *)(param_1 + 0x68),local_8,local_c,
                         *(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 0x8c),
                         *(undefined4 *)(param_1 + 0x90));
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x7c) = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x68);
    }
  }
  uVar4 = 0;
  if (*(int *)(param_1 + 0x7c) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x7c) + 0x30);
  }
  *param_2 = uVar2;
  if (*(int *)(param_1 + 0x74) == 0) {
    uVar4 = FUN_0048e1d5(3,&local_8,&local_c,&local_10);
    if (uVar4 == 0) {
      uVar4 = FUN_0048e385(3,&local_8,&local_c,&local_10);
      uVar4 = uVar4 | 0x10;
      if (uVar4 == 0x10) {
        uVar4 = 0;
        goto LAB_004a2f80;
      }
    }
    if (((local_8 < *(int *)(param_1 + 8)) ||
        (*(int *)(param_1 + 8) + *(int *)(param_1 + 0x14) <= local_8)) ||
       ((local_c < *(int *)(param_1 + 0xc) ||
        (*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10) <= local_c)))) {
      uVar4 = 0;
    }
    else {
      if ((uVar4 & 3) == 3) {
        uVar4 = uVar4 & 0xfffffffd;
      }
      if ((uVar4 & 0x10) == 0) {
        FUN_0048e169(uVar4,&local_8,&local_c,&local_10);
      }
      else {
        FUN_0048e319(uVar4,&local_8,&local_c,&local_10);
      }
      iVar1 = FUN_0049f4c2(param_1,local_8,local_c,param_1 + 0x88,param_1 + 0x8c,param_1 + 0x90);
      if ((iVar1 != 0) && ((*(uint *)(iVar1 + 0x108) & uVar4) == 0)) {
        iVar1 = 0;
      }
      *(int *)(param_1 + 0x74) = iVar1;
      *(uint *)(param_1 + 0x80) = uVar4;
      if (*(int *)(param_1 + 0x74) != 0) {
        *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(*(int *)(param_1 + 0x74) + 0x48);
        local_2c = local_8;
        local_28 = local_c;
        local_24 = *(undefined4 *)(param_1 + 0x88);
        local_20 = *(undefined4 *)(param_1 + 0x8c);
        local_1c = *(undefined4 *)(param_1 + 0x90);
        local_18 = *(uint *)(param_1 + 0x80);
        FUN_004a2847(*(undefined4 *)(param_1 + 0x74),&local_2c);
      }
    }
  }
  else {
    iVar1 = FUN_0048e241(*(undefined4 *)(param_1 + 0x80),&local_8,&local_c,&local_10);
    if (iVar1 != 0) {
      if (((*(int *)(param_1 + 0x7c) != 0) && (*(int *)(param_1 + 0x7c) == *(int *)(param_1 + 0x74))
          ) && (*(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x7c),
               (*(byte *)(*(int *)(param_1 + 0x78) + 0x28) & 2) != 0)) {
        *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(*(int *)(param_1 + 0x78) + 0x30);
      }
      FUN_004a2962(*(undefined4 *)(param_1 + 0x74),local_8,local_c,*(undefined4 *)(param_1 + 0x88),
                   *(undefined4 *)(param_1 + 0x8c),*(undefined4 *)(param_1 + 0x90),
                   *(undefined4 *)(param_1 + 0x80));
      *(undefined4 *)(param_1 + 0x74) = 0;
    }
  }
LAB_004a2f80:
  if (*(int *)(param_1 + 0x6c) == 0) {
    iVar1 = FUN_004a2be7(param_1,0,0,0,0);
    if ((iVar1 != 0) && (iVar3 = FUN_004a2be7(param_1,0,3,iVar1,0), iVar3 == 0)) {
      iVar3 = FUN_004a240f(param_1,iVar1);
      *(int *)(param_1 + 0x6c) = iVar3;
      if (iVar3 == 0) {
        iVar1 = FUN_004a2498(param_1,iVar1);
        if (iVar1 == 0) {
          if ((*(byte *)(param_1 + 0x1c) & 0x40) == 0) {
            FUN_004a2be7(param_1,0,2,0,0);
          }
        }
        else {
          FUN_004a2be7(param_1,0,2,0,0);
        }
      }
      else {
        FUN_004a2be7(param_1,0,1,0,0);
        uVar4 = 8;
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x6c);
    if ((*(byte *)(*(int *)(param_1 + 0x70) + 0x28) & 2) != 0) {
      *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x30);
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  if (uVar4 == 0) {
    if (*(int *)(param_1 + 0x68) != 0) {
      if (*(int *)(param_1 + 0x74) == 0) {
        if ((*(int *)(param_1 + 0x78) != 0) || (*(int *)(param_1 + 0x70) != 0)) {
          FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,9,0,*(undefined4 *)(param_1 + 0x88)
                      );
          FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,0x3d,1,
                       *(undefined4 *)(param_1 + 0x88));
          if ((*(int *)(param_1 + 0x68) == *(int *)(param_1 + 0x78)) ||
             (*(int *)(param_1 + 0x68) == *(int *)(param_1 + 0x70))) {
            FUN_004a2376(param_1,*(undefined4 *)(param_1 + 0x68),local_10);
            if (*(int *)(param_1 + 0x94) == 0) {
              *(undefined4 *)(param_1 + 0x78) = 0;
            }
            else {
              *param_2 = *(undefined4 *)(param_1 + 0x94);
              *(undefined4 *)(param_1 + 100) = 0;
            }
          }
        }
        *(undefined4 *)(param_1 + 0x68) = 0;
      }
      else {
        iVar1 = *(int *)(param_1 + 0x7c);
        if (*(int *)(*(int *)(param_1 + 0x68) + 0x1c) == 4) {
          iVar1 = *(int *)(param_1 + 0x68);
        }
        FUN_004a2c32(param_1,*(undefined4 *)(param_1 + 0x68));
        if ((iVar1 == *(int *)(param_1 + 0x68)) &&
           (*(int *)(param_1 + 0x88) == *(int *)(param_1 + 0x84))) {
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
        FUN_004a228a(param_1,*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x88),uVar2);
        if (iVar1 == *(int *)(param_1 + 0x68)) {
          uVar2 = FUN_0049f31e(param_1,*(undefined4 *)(param_1 + 0x68),local_8,local_c,0,0);
          FUN_004a2238(param_1,*(undefined4 *)(param_1 + 0x68),uVar2);
          local_2c = local_8;
          local_28 = local_c;
          local_24 = *(undefined4 *)(param_1 + 0x88);
          local_20 = *(undefined4 *)(param_1 + 0x8c);
          local_1c = *(undefined4 *)(param_1 + 0x90);
          local_18 = *(uint *)(param_1 + 0x80) | 0x20;
          FUN_004a2847(iVar1,&local_2c);
        }
        else {
          FUN_004a29cb(*(undefined4 *)(param_1 + 0x68),local_8,local_c,
                       *(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 0x8c),
                       *(undefined4 *)(param_1 + 0x90));
        }
      }
    }
  }
  else {
    if (*(int *)(param_1 + 0x74) == 0) {
      iVar1 = *(int *)(param_1 + 0x6c);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x74);
    }
    if ((*(int *)(param_1 + 0x68) != 0) && (iVar1 != *(int *)(param_1 + 0x68))) {
      FUN_004a228a(param_1,*(undefined4 *)(param_1 + 0x68),0,0);
      FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,0x3d,1,*(undefined4 *)(param_1 + 0x88))
      ;
    }
    *(int *)(param_1 + 0x68) = iVar1;
    FUN_004a228a(param_1,*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x88),1);
    uVar2 = FUN_0049f31e(param_1,*(undefined4 *)(param_1 + 0x68),local_8,local_c,0,0);
    FUN_004a2238(param_1,*(undefined4 *)(param_1 + 0x68),uVar2);
    if (*(int *)(param_1 + 0x68) != 0) {
      FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,0x3d,0,*(undefined4 *)(param_1 + 0x88))
      ;
    }
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    FUN_0048c434(local_14);
  }
  return *(int *)(param_1 + 0x74) != 0;
}

