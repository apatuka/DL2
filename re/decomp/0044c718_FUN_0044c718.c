// FUN_0044c718 @ 0044c718 size=58 sig=undefined FUN_0044c718() cc=unknown
// callers: FUN_004068f8,FUN_004484fc,IsBuildTaskDifferent,FUN_0040854c,FUN_0044f3f0,FUN_0041b500,FUN_004489e0,FUN_004067d0
// callees: CanUpgradeBuilding

int FUN_0044c718(int param_1)

{
  int iVar1;
  
  iVar1 = CanUpgradeBuilding(param_1);
  if (iVar1 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = ((int)*(short *)(&DAT_004f9df8 + *(char *)(param_1 + 4) * 0x32) -
            (int)*(short *)(&DAT_004f9dc6 + *(char *)(param_1 + 4) * 0x32)) * 3;
  }
  return iVar1;
}

