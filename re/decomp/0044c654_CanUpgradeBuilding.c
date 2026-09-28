// CanUpgradeBuilding @ 0044c654 size=193 sig=undefined CanUpgradeBuilding() cc=unknown
// callers: GetBuildingTasks,FUN_0040854c,FUN_0047f670,FUN_0044f3f0,FUN_004489e0,FUN_0044c718
// callees: DebugMessage
// strings: \"NULL building in CanUpgradeBuilding()\"

/* auto-named from string evidence: CanUpgradeBuilding */

undefined4 CanUpgradeBuilding(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 == 0) {
    DebugMessage(s_NULL_building_in_CanUpgradeBuild_004c6067);
    uVar1 = 0;
  }
  else {
    iVar2 = (int)*(char *)(param_1 + 4);
    if (((((((&DAT_005a43f0)[*(short *)(param_1 + 8) * 0xadc] == 0xff) || (0x2e < iVar2)) ||
          (*(char *)(param_1 + 5) == '\x12')) || ((*(char *)(param_1 + 5) == '\v' || (iVar2 == 3))))
        || ((iVar2 == 0x10 ||
            ((iVar2 == 0x2b ||
             ((&DAT_004f9dc3)[iVar2 * 0x32] != (&DAT_004f9dc3)[(iVar2 + 1) * 0x32])))))) ||
       (((char)(&DAT_004f9de3)[(iVar2 + 1) * 0x32] != 0 &&
        ((1 << ((&DAT_005a43f0)[*(short *)(param_1 + 8) * 0xadc] & 0x1f) &
         (int)(short)(&DAT_004fbbac)[(char)(&DAT_004f9de3)[(iVar2 + 1) * 0x32] * 0x19]) == 0)))) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

