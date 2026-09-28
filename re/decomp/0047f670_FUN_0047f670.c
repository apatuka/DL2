// FUN_0047f670 @ 0047f670 size=183 sig=undefined FUN_0047f670() cc=unknown
// callers: FUN_00480150
// callees: FUN_0047e074,CanUpgradeBuilding,FUN_00459864

void FUN_0047f670(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_8;
  
  if ((((param_3 != 0) && ((*(byte *)(param_3 + 2) & 4) != 0)) &&
      ((*(char *)(param_4 + 0x66 + DAT_0058f1f4) == '\x04' || (DAT_00583c20 != 0)))) &&
     ((DAT_004d5aa0 == '\0' && (*(char *)(param_3 + 0x2c) == '\x15')))) {
    if (*(int *)(param_3 + 0x18) == 0) {
      iVar2 = CanUpgradeBuilding(param_3);
      if (iVar2 == 0) {
        return;
      }
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
    iVar2 = param_1 + 0x2c;
    iVar3 = param_2 + 0xf;
    if ((&DAT_004f9dc5)[*(char *)(param_3 + 4) * 0x32] == '\x02') {
      iVar2 = param_1 + -6;
      iVar3 = param_2 + 5;
    }
    iVar1 = FUN_0047e074();
    if (iVar1 != 0) {
      FUN_00459864(iVar1,0x3f5,local_8,iVar2,iVar3);
    }
  }
  return;
}

