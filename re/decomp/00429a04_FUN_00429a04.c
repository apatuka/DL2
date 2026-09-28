// FUN_00429a04 @ 00429a04 size=1672 sig=undefined FUN_00429a04() cc=unknown
// callers: FUN_0042a25c
// callees: FUN_0049fd2e,FUN_00441388,FUN_0049fca2,FUN_004412d4,FUN_004a10d0

void FUN_00429a04(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  int *piVar12;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int *local_38;
  int *local_34;
  int *local_30;
  int *local_2c;
  undefined4 *local_28;
  int *local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  iVar2 = FUN_004a10d0(DAT_004b9bf0,0x47);
  if (((((iVar2 != 0) && (iVar3 = FUN_004a10d0(DAT_004b9bf0,0x4c), iVar3 != 0)) &&
       (iVar4 = FUN_004a10d0(DAT_004b9bf0,0x48), iVar4 != 0)) &&
      ((iVar5 = FUN_004a10d0(DAT_004b9bf0,0x4b), iVar5 != 0 &&
       (iVar6 = FUN_004a10d0(DAT_004b9bf0,0x49), iVar6 != 0)))) &&
     ((iVar7 = FUN_004a10d0(DAT_004b9bf0,0x4a), iVar7 != 0 &&
      ((iVar8 = FUN_004a10d0(DAT_004b9bf0,0x46), iVar8 != 0 &&
       (iVar9 = FUN_0049fca2(iVar7,0,*(undefined4 *)(iVar7 + 0x54),0,&local_48,&local_44),
       iVar9 != 0)))))) {
    local_40 = 0;
    local_30 = &DAT_004b9d7c;
    do {
      local_34 = local_30;
      local_38 = &DAT_004b9ddc;
      for (local_3c = 0; local_3c < 6 - local_40; local_3c = local_3c + 1) {
        iVar9 = 0;
        piVar10 = local_34;
        piVar12 = local_38;
        do {
          local_20 = *piVar10;
          local_1c = *piVar12;
          local_18 = local_20 + local_48;
          local_14 = local_1c + local_44;
          FUN_0049fd2e(iVar8,&local_20,0,0,0,*(undefined4 *)(iVar8 + 0x54),0);
          iVar9 = iVar9 + 1;
          piVar12 = piVar12 + 1;
          piVar10 = piVar10 + 1;
        } while (iVar9 < 4);
        local_38 = local_38 + 4;
      }
      local_40 = local_40 + 1;
      local_30 = local_30 + 4;
    } while (local_40 < 6);
    local_28 = &DAT_00557bb4;
    local_2c = &DAT_004b9d7c;
    for (local_40 = 0; local_40 < DAT_004d5aec + -1; local_40 = local_40 + 1) {
      local_20 = *local_2c;
      local_1c = DAT_004b9ddc;
      local_18 = local_20 + local_48;
      local_14 = DAT_004b9ddc + local_44;
      iVar8 = FUN_004412d4(DAT_0058f1f4,*local_28,1);
      if (iVar8 == 0) {
        iVar8 = FUN_004412d4(DAT_0058f1f4,*local_28,2);
        if (iVar8 == 0) {
          FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
        }
        else {
          FUN_0049fd2e(iVar6,&local_20,0,0,0,*(undefined4 *)(iVar6 + 0x54),0);
        }
      }
      else {
        FUN_0049fd2e(iVar4,&local_20,0,0,0,*(undefined4 *)(iVar4 + 0x54),0);
      }
      local_20 = local_2c[1];
      local_1c = DAT_004b9de0;
      local_18 = local_20 + local_48;
      local_14 = DAT_004b9de0 + local_44;
      iVar8 = FUN_004412d4(DAT_0058f1f4,*local_28,0x10);
      if (iVar8 == 0) {
        FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
      }
      else {
        FUN_0049fd2e(iVar7,&local_20,0,0,0,*(undefined4 *)(iVar7 + 0x54),0);
      }
      local_20 = local_2c[2];
      local_1c = DAT_004b9de4;
      local_18 = local_20 + local_48;
      local_14 = DAT_004b9de4 + local_44;
      iVar8 = FUN_004412d4(DAT_0058f1f4,*local_28,8);
      if (iVar8 == 0) {
        FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
      }
      else {
        FUN_0049fd2e(iVar5,&local_20,0,0,0,*(undefined4 *)(iVar5 + 0x54),0);
      }
      local_20 = local_2c[3];
      local_1c = DAT_004b9de8;
      local_18 = local_20 + local_48;
      local_14 = DAT_004b9de8 + local_44;
      iVar8 = FUN_004412d4(DAT_0058f1f4,*local_28,4);
      if (iVar8 == 0) {
        FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
      }
      else {
        FUN_0049fd2e(iVar3,&local_20,0,0,0,*(undefined4 *)(iVar3 + 0x54),0);
      }
      puVar1 = local_28;
      local_3c = (DAT_004d5aec + -3) - local_40;
      puVar11 = &DAT_00557bcc + local_3c;
      piVar10 = (int *)(&DAT_004b9dec + local_3c * 0x10);
      local_24 = local_2c;
      for (; -1 < local_3c; local_3c = local_3c + -1) {
        local_20 = *local_24;
        local_1c = *piVar10;
        local_18 = local_20 + local_48;
        local_14 = local_1c + local_44;
        iVar8 = FUN_00441388(*puVar11,*puVar1,1);
        if (iVar8 == 0) {
          iVar8 = FUN_00441388(*puVar11,*puVar1,2);
          if (iVar8 == 0) {
            FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
          }
          else {
            FUN_0049fd2e(iVar6,&local_20,0,0,0,*(undefined4 *)(iVar6 + 0x54),0);
          }
        }
        else {
          FUN_0049fd2e(iVar4,&local_20,0,0,0,*(undefined4 *)(iVar4 + 0x54),0);
        }
        local_20 = local_24[1];
        local_1c = piVar10[1];
        local_18 = local_20 + local_48;
        local_14 = local_1c + local_44;
        iVar8 = FUN_00441388(*puVar11,*puVar1,0x10);
        if (iVar8 == 0) {
          FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
        }
        else {
          FUN_0049fd2e(iVar7,&local_20,0,0,0,*(undefined4 *)(iVar7 + 0x54),0);
        }
        local_20 = local_24[2];
        local_1c = piVar10[2];
        local_18 = local_20 + local_48;
        local_14 = local_1c + local_44;
        iVar8 = FUN_00441388(*puVar11,*puVar1,8);
        if (iVar8 == 0) {
          FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
        }
        else {
          FUN_0049fd2e(iVar5,&local_20,0,0,0,*(undefined4 *)(iVar5 + 0x54),0);
        }
        local_20 = local_24[3];
        local_1c = piVar10[3];
        local_18 = local_20 + local_48;
        local_14 = local_1c + local_44;
        iVar8 = FUN_00441388(*puVar11,*puVar1,4);
        if (iVar8 == 0) {
          FUN_0049fd2e(iVar2,&local_20,0,0,0,*(undefined4 *)(iVar2 + 0x54),0);
        }
        else {
          FUN_0049fd2e(iVar3,&local_20,0,0,0,*(undefined4 *)(iVar3 + 0x54),0);
        }
        puVar11 = puVar11 + -1;
        piVar10 = piVar10 + -4;
      }
      local_28 = local_28 + 1;
      local_2c = local_2c + 4;
    }
  }
  return;
}

