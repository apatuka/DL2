// TotalTaskLabor @ 0044b714 size=193 sig=undefined TotalTaskLabor() cc=unknown
// callers: 
// callees: FUN_0044eb4c,DebugMessage
// strings: \"NULL pTerritory in TotalTaskLabor()\"|\"Invalid pTerritory in TotalTaskLabor()\"

/* auto-named from string evidence: TotalTaskLabor */

int TotalTaskLabor(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int local_24 [5];
  int *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_8 = 0;
  if (param_1 == 0) {
    DebugMessage(s_NULL_pTerritory_in_TotalTaskLabo_004c5f47);
    local_8 = 0;
  }
  else if ((param_2 < 1) || (0x15 < param_2)) {
    DebugMessage(s_Invalid_pTerritory_in_TotalTaskL_004c5f6b);
    local_8 = 0;
  }
  else {
    local_c = &DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8;
    iVar5 = 0;
    local_10 = (int *)(param_1 + 0x154);
    do {
      iVar1 = *local_10;
      if (iVar1 != 0) {
        FUN_0044eb4c(local_c,param_1,iVar5,local_24,0);
        iVar4 = 0;
        piVar3 = local_24;
        pcVar2 = (char *)(iVar1 + 0x2c);
        do {
          if (param_2 == *pcVar2) {
            local_8 = local_8 + *piVar3;
            break;
          }
          iVar4 = iVar4 + 1;
          piVar3 = piVar3 + 1;
          pcVar2 = pcVar2 + 1;
        } while (iVar4 < 5);
      }
      iVar5 = iVar5 + 1;
      local_10 = local_10 + 0xd;
    } while (iVar5 < 0x24);
  }
  return local_8;
}

