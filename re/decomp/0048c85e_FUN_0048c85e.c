// FUN_0048c85e @ 0048c85e size=932 sig=undefined FUN_0048c85e() cc=unknown
// callers: FUN_00480150,DrawCAGuyPool,FUN_004943ab,FUN_004878a8,FUN_004a034a,FUN_0043e22c,FUN_004a322d,FUN_00425f58,FUN_00413348,FUN_004649c0,FUN_00422344,FUN_0049483f,FUN_00458c6c,FUN_00494b6b,FUN_00414f38,FUN_00494449,FUN_00487e34,FUN_00464b90,FUN_00418704,FUN_004897ea,FUN_0041ba74,FUN_00426140,FUN_00444398,FUN_0048960b
// callees: FUN_00495cc4,FUN_0048be22,ShowCursor,EnterCriticalSection,FUN_0048c662,FUN_0048c2c5,GetCursorPos,FUN_0048c3f4,LeaveCriticalSection,FUN_00495c51

void FUN_0048c85e(undefined *param_1,undefined *param_2,int *param_3,int *param_4,int param_5,
                 int param_6,int param_7)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_40 [4];
  int local_30 [4];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  tagPOINT local_c;
  
  local_10 = 0;
  if (param_3 == (int *)0x0) {
    local_30[1] = DAT_0065e570;
    local_30[0] = DAT_0065e574;
    local_30[3] = DAT_0065e578;
    local_30[2] = DAT_0065e57c;
  }
  else {
    piVar3 = local_30;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *param_3;
      param_3 = param_3 + 1;
      piVar3 = piVar3 + 1;
    }
  }
  if (param_4 == (int *)0x0) {
    local_40[1] = DAT_0065e570;
    local_40[0] = DAT_0065e574;
    local_40[3] = DAT_0065e578;
    local_40[2] = DAT_0065e57c;
  }
  else {
    piVar3 = local_40;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *param_4;
      param_4 = param_4 + 1;
      piVar3 = piVar3 + 1;
    }
  }
  local_1c = local_40[0];
  local_20 = local_40[1];
  if (local_40[0] < 0) {
    local_40[0] = 0;
  }
  if (*(int *)(param_2 + 4) <= local_40[2]) {
    local_40[2] = *(int *)(param_2 + 4);
  }
  if (local_40[1] < 0) {
    local_40[1] = 0;
  }
  if (*(int *)(param_2 + 8) <= local_40[3]) {
    local_40[3] = *(int *)(param_2 + 8);
  }
  if ((param_6 == 0) || (iVar1 = FUN_00495cc4(local_40,param_6), iVar1 != 0)) {
    local_30[0] = local_30[0] + (local_40[0] - local_1c);
    local_30[1] = local_30[1] + (local_40[1] - local_20);
    local_1c = local_30[0];
    local_20 = local_30[1];
    if (local_30[0] < 0) {
      local_30[0] = 0;
    }
    if (*(int *)(param_1 + 4) <= local_30[2]) {
      local_30[2] = *(int *)(param_1 + 4);
    }
    if (local_30[1] < 0) {
      local_30[1] = 0;
    }
    if (*(int *)(param_1 + 8) <= local_30[3]) {
      local_30[3] = *(int *)(param_1 + 8);
    }
    if ((param_5 == 0) || (iVar1 = FUN_00495cc4(local_30,param_5), iVar1 != 0)) {
      iVar2 = local_30[0] - local_1c;
      iVar1 = local_30[1] - local_20;
      local_30[0] = local_30[0] + *(int *)(param_1 + 0x14);
      local_30[1] = local_30[1] + *(int *)(param_1 + 0x18);
      local_30[2] = local_30[2] + *(int *)(param_1 + 0x14);
      local_30[3] = local_30[3] + *(int *)(param_1 + 0x18);
      local_40[0] = local_40[0] + iVar2 + *(int *)(param_2 + 0x14);
      local_40[1] = local_40[1] + iVar1 + *(int *)(param_2 + 0x18);
      if (local_30[3] - local_30[1] < (local_40[3] + *(int *)(param_2 + 0x18)) - local_40[1]) {
        iVar1 = local_30[3] - local_30[1];
      }
      else {
        iVar1 = (local_40[3] + *(int *)(param_2 + 0x18)) - local_40[1];
      }
      if (local_30[2] - local_30[0] < (local_40[2] + *(int *)(param_2 + 0x14)) - local_40[0]) {
        iVar2 = local_30[2] - local_30[0];
      }
      else {
        iVar2 = (local_40[2] + *(int *)(param_2 + 0x14)) - local_40[0];
      }
      if ((0 < iVar2) && (0 < iVar1)) {
        local_30[2] = local_30[0] + iVar2;
        local_30[3] = local_30[1] + iVar1;
        local_40[2] = iVar2 + local_40[0];
        local_40[3] = iVar1 + local_40[1];
        if ((*(short *)(param_1 + 0x2a) == 0) &&
           (((*(short *)(param_2 + 0x2a) == 0 &&
             (*(int *)(param_1 + 0xc) == *(int *)(param_2 + 0xc))) && (param_7 == 0)))) {
          GetCursorPos(&local_c);
          if (((param_1 == &DAT_0065e644) || (param_2 == &DAT_0065e644)) && (DAT_0051b83c != 0)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
          if ((((*(ushort *)(param_2 + 0x28) & 6) == 6) && (local_40[0] + -0x20 <= local_c.x)) &&
             ((local_c.x < local_40[2] + 0x20 &&
              ((local_40[1] + -0x20 <= local_c.y && (local_c.y < local_40[3] + 0x20)))))) {
            ShowCursor(0);
            local_10 = 1;
          }
          local_14 = (int)*(short *)(param_2 + 0x24);
          if (0 < local_14) {
            FUN_0048c3f4(param_2);
          }
          local_18 = (int)*(short *)(param_1 + 0x24);
          if (0 < local_18) {
            FUN_0048c3f4(param_1);
          }
          (**(code **)(**(int **)(param_2 + 0x40) + 0x14))
                    (*(int **)(param_2 + 0x40),local_40,*(undefined4 *)(param_1 + 0x40),local_30,
                     0x1000000,0);
          if (local_18 != 0) {
            FUN_0048c2c5(param_1);
          }
          if (local_14 != 0) {
            FUN_0048c2c5(param_2);
          }
          if (local_10 != 0) {
            ShowCursor(1);
          }
          if (((param_1 == &DAT_0065e644) || (param_2 == &DAT_0065e644)) && (DAT_0051b83c != 0)) {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
        }
        else {
          if (((param_1 == &DAT_0065e644) || (param_2 == &DAT_0065e644)) && (DAT_0051b83c != 0)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
          if (((*(short *)(param_1 + 0x2a) == 1) &&
              ((param_2 == (undefined *)0x0 || (param_2 == &DAT_0065e644)))) && (param_7 == 0)) {
            FUN_00495c51(local_40,-*(int *)(param_2 + 0x14),-*(int *)(param_2 + 0x18));
            FUN_0048be22(param_1,local_30,local_40);
          }
          else {
            FUN_0048c662(param_1,param_2,local_30,local_40,param_7);
          }
          if (((param_1 == &DAT_0065e644) || (param_2 == &DAT_0065e644)) && (DAT_0051b83c != 0)) {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
        }
      }
    }
  }
  return;
}

