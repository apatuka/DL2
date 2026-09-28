// FUN_0049c5e7 @ 0049c5e7 size=297 sig=undefined FUN_0049c5e7() cc=unknown
// callers: FUN_0049c710
// callees: FUN_004935fc

void FUN_0049c5e7(int param_1,undefined4 param_2,int param_3,int param_4,int *param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_8;
  
  if ((param_3 == 0) || (param_3 == 2)) {
    iVar1 = (param_5[3] - param_5[1]) / 3;
    uVar2 = (param_5[3] - param_5[1]) - iVar1;
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    iVar3 = iVar3 + param_5[1];
    iVar4 = param_5[2] - *param_5 >> 1;
    if (iVar4 < 0) {
      iVar4 = iVar4 + (uint)((param_5[2] - *param_5 & 1U) != 0);
    }
    iVar5 = *param_5;
    if (param_3 == 0) {
      local_8 = 0;
      param_3 = 1;
    }
    else {
      local_8 = iVar1 + -1;
      param_3 = -1;
    }
    while (iVar1 != 0) {
      FUN_004935fc((iVar4 + iVar5) - local_8,iVar3,local_8 + iVar4 + iVar5 + 1,iVar3 + 1,
                   *(undefined4 *)(param_1 + 0x114 + param_4 * 4));
      iVar3 = iVar3 + 1;
      local_8 = local_8 + param_3;
      iVar1 = iVar1 + -1;
    }
  }
  else {
    local_8 = (param_5[2] - *param_5) / 3;
    uVar2 = (param_5[2] - *param_5) - local_8;
    iVar1 = (int)uVar2 >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((uVar2 & 1) != 0);
    }
    iVar1 = iVar1 + *param_5;
    iVar3 = param_5[3] - param_5[1] >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((param_5[3] - param_5[1] & 1U) != 0);
    }
    iVar4 = param_5[1];
    if (param_3 == 3) {
      iVar5 = 0;
      param_3 = 1;
    }
    else {
      iVar5 = local_8 + -1;
      param_3 = -1;
    }
    while (local_8 != 0) {
      FUN_004935fc(iVar1,(iVar3 + iVar4) - iVar5,iVar1 + 1,iVar5 + iVar3 + iVar4,
                   *(undefined4 *)(param_1 + 0x114 + param_4 * 4));
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + param_3;
      local_8 = local_8 + -1;
    }
  }
  return;
}

