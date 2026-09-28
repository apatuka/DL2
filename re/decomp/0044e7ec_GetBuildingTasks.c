// GetBuildingTasks @ 0044e7ec size=460 sig=undefined GetBuildingTasks() cc=unknown
// callers: FUN_00485668,FUN_0047d068,FUN_0044f3f0,FUN_0046c1f0,FUN_0044d890
// callees: FUN_0044c49c,DebugMessage,FUN_0044ba18,CanUpgradeBuilding,FUN_0044e600
// strings: \"Invalid building in GetBuildingTasks()\"

/* auto-named from string evidence: GetBuildingTasks */

void GetBuildingTasks(byte *param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  undefined1 *local_18;
  undefined *local_14;
  int local_10;
  int local_c;
  
  uVar4 = 1 << (*param_1 & 0x1f);
  local_c = 0;
  if (param_2 == 0) {
    DebugMessage(s_Invalid_building_in_GetBuildingT_004c6166);
  }
  else if (*(short *)(param_2 + 0x14) == 0) {
    local_10 = -1;
    iVar6 = CanUpgradeBuilding(param_2);
    if (iVar6 == 0) {
      *(undefined1 *)(param_2 + 0x2c) = 0;
      local_c = *(int *)(param_2 + 0x18);
      *(undefined4 *)(param_2 + 0x18) = 0;
      *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & 0xfeff;
    }
    else {
      if ((*(char *)(param_2 + 0x2c) == '\x02') && ((*(byte *)(param_2 + 3) & 1) == 0)) {
        local_c = *(int *)(param_2 + 0x18);
        *(undefined4 *)(param_2 + 0x18) = 0;
      }
      *(undefined1 *)(param_2 + 0x2c) = 0x15;
      local_10 = 0;
    }
    local_18 = (undefined1 *)(param_2 + 0x2d);
    iVar6 = 1;
    piVar7 = (int *)(param_2 + 0x1c);
    local_14 = &DAT_004f9dbd;
    do {
      iVar3 = (int)(char)local_14[*(char *)(param_2 + 4) * 0x32 + 0x18];
      if ((iVar6 == 1) && ((*(char *)(param_2 + 4) == '.' || (*(char *)(param_2 + 4) == '/')))) {
        iVar3 = FUN_0044e600(param_2,1);
      }
      else {
        switch(local_14[*(char *)(param_2 + 4) * 0x32 + 0x18]) {
        case 4:
          if (((int)DAT_004fbf94 & uVar4) == 0) {
            iVar3 = 0;
          }
          break;
        case 6:
          if (((int)DAT_004fbc74 & uVar4) == 0) {
            iVar3 = 0;
          }
          break;
        case 9:
          if (((int)DAT_004fbc10 & uVar4) == 0) {
            iVar3 = 0;
          }
          break;
        case 10:
          if (((int)DAT_004fc156 & uVar4) == 0) {
            iVar3 = 0;
          }
          break;
        case 0x10:
          if (((int)DAT_004fbff8 & uVar4) == 0) {
            iVar3 = 0;
          }
        }
      }
      *local_18 = (char)iVar3;
      if (iVar3 == 0) {
        local_c = local_c + *piVar7;
        *piVar7 = 0;
      }
      else if (local_10 == -1) {
        local_10 = iVar6;
      }
      iVar6 = iVar6 + 1;
      piVar7 = piVar7 + 1;
      local_18 = local_18 + 1;
      local_14 = local_14 + 1;
    } while (iVar6 < 5);
    if (local_c != 0) {
      iVar6 = FUN_0044ba18(param_2);
      FUN_0044c49c(param_2,iVar6 + local_c);
    }
  }
  else {
    *(undefined1 *)(param_2 + 0x2c) = 2;
    uVar1 = FUN_0044ba18(param_2);
    *(undefined4 *)(param_2 + 0x18) = uVar1;
    iVar6 = 1;
    puVar5 = (undefined4 *)(param_2 + 0x1c);
    puVar2 = (undefined1 *)(param_2 + 0x2d);
    do {
      *puVar2 = 0;
      *puVar5 = 0;
      *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & ~(0x100 << ((byte)iVar6 & 0x1f));
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar6 < 5);
  }
  return;
}

