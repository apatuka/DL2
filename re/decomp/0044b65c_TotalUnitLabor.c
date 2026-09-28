// TotalUnitLabor @ 0044b65c size=181 sig=undefined TotalUnitLabor() cc=unknown
// callers: FUN_0041c418,FUN_004489e0,FUN_004105e8,FUN_0041ffd4
// callees: FUN_0044eb4c,DebugMessage
// strings: \"NULL pTerritory in TotalUnitLabor()\"|\"Invalid uqThis in TotalUnitLabor()\"

/* auto-named from string evidence: TotalUnitLabor */

int TotalUnitLabor(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined1 local_20 [16];
  int local_10;
  undefined1 *local_c;
  int local_8;
  
  local_8 = 0;
  if (param_1 == 0) {
    DebugMessage(s_NULL_pTerritory_in_TotalUnitLabo_004c5f00);
    local_8 = 0;
  }
  else if ((param_2 < 0) || (5 < param_2)) {
    DebugMessage(s_Invalid_uqThis_in_TotalUnitLabor_004c5f24);
    local_8 = 0;
  }
  else {
    local_c = &DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8;
    iVar1 = 0;
    piVar2 = (int *)(param_1 + 0x154);
    do {
      if ((*piVar2 != 0) && (param_2 == *(int *)(&DAT_004f9de6 + *(char *)(*piVar2 + 4) * 0x32))) {
        FUN_0044eb4c(local_c,param_1,iVar1,local_20,0);
        local_8 = local_8 + local_10;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xd;
    } while (iVar1 < 0x24);
  }
  return local_8;
}

