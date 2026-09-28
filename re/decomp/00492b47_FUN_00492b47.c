// FUN_00492b47 @ 00492b47 size=430 sig=undefined FUN_00492b47() cc=unknown
// callers: FUN_00493149,FUN_00492d67,FUN_004931b0,FUN_0049331e
// callees: FUN_00492290

int FUN_00492b47(byte *param_1,int param_2,int param_3,int *param_4,int *param_5,char param_6,
                int *param_7)

{
  int iVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte local_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  local_14 = -1;
  local_10 = 0;
  iVar6 = 0;
  local_1c = 0;
  local_21 = 0x20;
  bVar3 = false;
  local_20 = -1;
  local_c = *param_7;
  if ((param_6 != '\0') && ((*param_1 == 0x7b || (*param_1 == 0xfa)))) {
    iVar4 = FUN_00492290(*param_1);
    *param_7 = iVar4;
    pbVar5 = param_1;
    while (pbVar5 = pbVar5 + 1, *pbVar5 == 0x20) {
      iVar4 = FUN_00492290(0x20);
      *param_7 = *param_7 + iVar4;
    }
    local_c = 0;
  }
  while ((iVar4 = iVar6, *param_1 != 0 && (!bVar3))) {
    bVar2 = *param_1;
    if (local_10 == param_3) {
      local_20 = iVar4;
    }
    iVar6 = iVar4;
    if ((bVar2 == 0xd) || (bVar2 == 10)) {
      if (((bVar2 == 0xd) && (param_1[1] == 10)) || ((bVar2 == 10 && (param_1[1] == 0xd)))) {
        param_1 = param_1 + 1;
      }
      bVar3 = true;
      if (0x20 < local_21) {
        local_14 = local_10;
        local_18 = iVar4;
      }
      *param_7 = 0;
    }
    else {
      iVar1 = local_10 + 1;
      if (bVar2 == 0x20) {
        if (0x20 < local_21) {
          local_14 = local_10;
          local_18 = iVar4;
        }
        iVar6 = FUN_00492290(0x20);
        iVar6 = iVar4 + iVar6;
        local_10 = iVar1;
      }
      else if (bVar2 == 9) {
        iVar6 = (iVar4 / DAT_0051dc18) * DAT_0051dc18 + DAT_0051dc18;
        local_10 = iVar1;
      }
      else {
        local_10 = iVar1;
        if (0x20 < bVar2) {
          iVar6 = FUN_00492290(bVar2);
          iVar6 = iVar4 + iVar6;
        }
      }
    }
    if (param_2 - local_c < iVar6) {
      bVar3 = true;
    }
    param_1 = param_1 + 1;
    local_21 = bVar2;
    local_1c = iVar4;
  }
  if (((*param_1 == 0) && (0x20 < local_21)) && (!bVar3)) {
    local_14 = local_10;
    local_18 = iVar4;
  }
  if (local_14 == -1) {
    local_14 = local_10;
    local_18 = local_1c;
  }
  if (local_18 < local_20) {
    local_20 = -1;
  }
  *param_4 = local_14;
  *param_5 = local_18 + local_c;
  if (local_20 == -1) {
    local_20 = -1;
  }
  else {
    local_20 = local_20 + local_c;
  }
  return local_20;
}

