// FUN_004ab1a0 @ 004ab1a0 size=547 sig=undefined FUN_004ab1a0() cc=unknown
// callers: FUN_004aa9c4
// callees: FUN_004ade7b,FUN_004aff64,FUN_004adde0

longlong FUN_004ab1a0(code *param_1,code *param_2,undefined4 param_3,int param_4,int param_5,
                     int *param_6,int *param_7)

{
  int iVar1;
  bool bVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  longlong lVar8;
  longlong lVar9;
  int local_20;
  int local_1c;
  int local_14;
  int local_10;
  int local_c;
  
  iVar6 = 0;
  bVar7 = false;
  local_c = 0;
  local_10 = 1;
  local_14 = 0;
  iVar1 = local_c;
  lVar3 = 0;
LAB_004ab1d1:
  local_c = iVar1;
  iVar1 = local_c + 1;
  iVar4 = (*param_1)(param_3);
  if (iVar6 == 0) {
    if (((-1 < iVar4) && (iVar4 < 0x80)) && (iVar5 = FUN_004aff64(iVar4), iVar5 != 0))
    goto LAB_004ab1d1;
    iVar6 = 1;
  }
  iVar5 = param_5 + -1;
  if (iVar5 < 0) goto LAB_004ab375;
  if ((iVar6 == 1) && ((iVar6 = 2, iVar4 == 0x2b || (iVar4 == 0x2d)))) {
    bVar7 = iVar4 == 0x2d;
    param_5 = iVar5;
    goto LAB_004ab1d1;
  }
  if (iVar6 == 2) {
    iVar6 = 3;
    if ((iVar4 == 0x30) && ((local_14 = 1, param_4 == 0 || (param_4 == 0x10)))) {
      iVar1 = local_c + 2;
      iVar4 = (*param_1)(param_3);
      param_5 = param_5 + -2;
      if (param_5 < 0) goto LAB_004ab375;
      if ((iVar4 == 0x78) || (iVar4 == 0x58)) {
        param_4 = 0x10;
        goto LAB_004ab1d1;
      }
      iVar5 = param_5;
      if (param_4 == 0) {
        param_4 = 8;
      }
    }
    local_c = iVar1;
    param_5 = iVar5;
    iVar5 = param_5;
    iVar1 = local_c;
    if (param_4 == 0) {
      param_4 = 10;
    }
    else if ((param_4 < 1) || (0x24 < param_4)) goto LAB_004ab375;
  }
  local_c = iVar1;
  param_5 = iVar5;
  iVar1 = local_c;
  if (iVar6 == 3) {
    if ((iVar4 < 0x30) || (0x39 < iVar4)) {
      if ((iVar4 < 0x61) || (0x7a < iVar4)) {
        if ((iVar4 < 0x41) || (0x5a < iVar4)) goto LAB_004ab375;
        local_20 = iVar4 + -0x37;
      }
      else {
        local_20 = iVar4 + -0x57;
      }
    }
    else {
      local_20 = iVar4 + -0x30;
    }
    if (param_4 <= local_20) goto LAB_004ab375;
    local_14 = local_14 + 1;
    lVar8 = FUN_004adde0(param_4,param_4 >> 0x1f);
    lVar9 = FUN_004ade7b(param_4,param_4 >> 0x1f);
    bVar2 = lVar3 != lVar9;
    lVar3 = lVar8 + local_20;
    if (bVar2) {
      local_10 = 2;
      if (bVar7) {
        lVar3 = -0x8000000000000000;
      }
      else {
        lVar3 = 0x7fffffffffffffff;
      }
LAB_004ab375:
      local_c = iVar1;
      local_1c = (int)lVar3;
      if (local_10 != 2) {
        (*param_2)(iVar4,param_3);
        local_c = local_c + -1;
        if (bVar7) {
          lVar3 = (longlong)-local_1c;
        }
      }
      if ((local_14 == 0) && (local_10 = -1, iVar4 != -1)) {
        local_10 = 0;
      }
      *param_7 = local_10;
      *param_6 = *param_6 + local_c;
      return lVar3;
    }
  }
  goto LAB_004ab1d1;
}

