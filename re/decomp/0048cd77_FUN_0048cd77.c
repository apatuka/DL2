// FUN_0048cd77 @ 0048cd77 size=520 sig=undefined FUN_0048cd77() cc=unknown
// callers: 
// callees: FUN_00495cc4,FUN_0048cc02

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 FUN_0048cd77(int param_1,int param_2,int *param_3,int *param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_34 [4];
  int local_24 [4];
  int local_14;
  int local_10;
  
  if (param_3 == (int *)0x0) {
    local_24[1] = DAT_0065e570;
    local_24[0] = DAT_0065e574;
    local_24[3] = DAT_0065e578;
    local_24[2] = DAT_0065e57c;
  }
  else {
    piVar6 = local_24;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar6 = *param_3;
      param_3 = param_3 + 1;
      piVar6 = piVar6 + 1;
    }
  }
  if (param_4 == (int *)0x0) {
    local_34[1] = DAT_0065e570;
    local_34[0] = DAT_0065e574;
    local_34[3] = DAT_0065e578;
    local_34[2] = DAT_0065e57c;
  }
  else {
    piVar6 = local_34;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar6 = *param_4;
      param_4 = param_4 + 1;
      piVar6 = piVar6 + 1;
    }
  }
  local_10 = local_34[0];
  local_14 = local_34[1];
  if (local_34[0] < 0) {
    local_34[0] = 0;
  }
  if (*(int *)(param_2 + 4) <= local_34[2]) {
    local_34[2] = *(int *)(param_2 + 4);
  }
  if (local_34[1] < 0) {
    local_34[1] = 0;
  }
  if (*(int *)(param_2 + 8) <= local_34[3]) {
    local_34[3] = *(int *)(param_2 + 8);
  }
  if ((param_6 == 0) || (iVar1 = FUN_00495cc4(local_34,param_6), iVar1 != 0)) {
    local_24[0] = local_24[0] + (local_34[0] - local_10);
    local_24[1] = local_24[1] + (local_34[1] - local_14);
    local_10 = local_24[0];
    local_14 = local_24[1];
    if (local_24[0] < 0) {
      local_24[0] = 0;
    }
    if (*(int *)(param_1 + 4) <= local_24[2]) {
      local_24[2] = *(int *)(param_1 + 4);
    }
    if (local_24[1] < 0) {
      local_24[1] = 0;
    }
    if (*(int *)(param_1 + 8) <= local_24[3]) {
      local_24[3] = *(int *)(param_1 + 8);
    }
    if ((param_5 == 0) || (iVar1 = FUN_00495cc4(local_24,param_5), iVar1 != 0)) {
      iVar5 = local_24[0] - local_10;
      iVar4 = local_24[1] - local_14;
      local_24[0] = local_24[0] + *(int *)(param_1 + 0x14);
      local_24[1] = local_24[1] + *(int *)(param_1 + 0x18);
      iVar1 = local_24[2] + *(int *)(param_1 + 0x14);
      iVar3 = local_24[3] + *(int *)(param_1 + 0x18);
      local_34[0] = local_34[0] + iVar5 + *(int *)(param_2 + 0x14);
      local_34[1] = local_34[1] + iVar4 + *(int *)(param_2 + 0x18);
      iVar4 = local_34[2] + *(int *)(param_2 + 0x14);
      iVar5 = local_34[3] + *(int *)(param_2 + 0x18);
      if (iVar3 - local_24[1] < iVar5 - local_34[1]) {
        iVar3 = iVar3 - local_24[1];
      }
      else {
        iVar3 = iVar5 - local_34[1];
      }
      if (iVar1 - local_24[0] < iVar4 - local_34[0]) {
        iVar1 = iVar1 - local_24[0];
      }
      else {
        iVar1 = iVar4 - local_34[0];
      }
      if ((iVar1 < 1) || (iVar3 < 1)) {
        uVar2 = 2;
      }
      else {
        local_24[2] = local_24[0] + iVar1;
        local_24[3] = local_24[1] + iVar3;
        local_34[2] = iVar1 + local_34[0];
        local_34[3] = iVar3 + local_34[1];
        uVar2 = FUN_0048cc02(param_1,param_2,local_24,local_34);
      }
    }
    else {
      uVar2 = 2;
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

