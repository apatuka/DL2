// FUN_00472974 @ 00472974 size=633 sig=undefined FUN_00472974() cc=unknown
// callers: FUN_004720f4,FUN_00472018,ConsumeFood,FUN_00472bf0,FUN_00472ca0,FUN_0044f3f0
// callees: FUN_004589a0,FUN_004237d0,FUN_00472844,FUN_00471a98
// strings: \"Collect Material\"

int FUN_00472974(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6,
                int *param_7)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  if (param_5 == 0) {
    local_c = *(undefined4 *)(param_1 + 0xad6);
  }
  local_10 = 2;
  if ((1 << ((byte)param_2 & 0x1f) & (int)DAT_004fc4a8) != 0) {
    local_10 = 3;
  }
  FUN_004589a0(s_Collect_Material_004d63c3);
  piVar1 = (int *)(param_1 + 0x3a + param_3 * 4);
  do {
    if (param_4 < 1) {
LAB_00472bb5:
      if (param_5 == 0) {
        *(undefined4 *)(param_1 + 0xad6) = local_c;
      }
      *param_6 = param_4;
      *param_7 = local_8;
      if (param_4 != 0) {
        local_8 = -1;
      }
      return local_8;
    }
    if (((*(int *)(param_1 + 0xad6) == 0) ||
        (*(int *)(*(int *)(param_1 + 0xad6) + 0x3a + param_3 * 4) <=
         *(int *)(*(int *)(param_1 + 0xad6) + 0xa7e + param_3 * 4))) &&
       (iVar2 = FUN_00472844(param_1,param_2,param_3,local_10), iVar2 == 0)) {
      if ((param_5 != 0) && (DAT_00653434 != 0)) {
        FUN_004237d0(param_2,0x3c,param_1,(&PTR_s_credits_005090c4)[param_3],0,0,
                     (int)*(short *)(param_1 + 0x1a),param_3);
      }
      goto LAB_00472bb5;
    }
    if ((*(int *)(param_1 + 0xad6) == 0) ||
       ((int)(&DAT_0059f16c)[param_2 * 0xb6] < (int)*(short *)(param_1 + 0xada))) {
      *(undefined4 *)(param_1 + 0xad6) = 0;
    }
    else {
      local_18 = *(int *)(*(int *)(param_1 + 0xad6) + 0x3a + param_3 * 4) -
                 *(int *)(*(int *)(param_1 + 0xad6) + 0xa7e + param_3 * 4);
      if (param_4 < local_18) {
        piVar3 = &param_4;
      }
      else {
        piVar3 = &local_18;
      }
      local_14 = *piVar3;
      if (*(short *)(param_1 + 0xada) == 0) {
        piVar3 = &DAT_0059f16c + param_2 * 0xb6;
        if (local_14 < *piVar3) {
          piVar3 = &local_14;
        }
        local_14 = *piVar3;
      }
      else {
        local_1c = (int)(&DAT_0059f16c)[param_2 * 0xb6] / (int)*(short *)(param_1 + 0xada);
        if (local_14 < local_1c) {
          piVar3 = &local_14;
        }
        else {
          piVar3 = &local_1c;
        }
        local_14 = *piVar3;
      }
      local_20 = 10000 - *piVar1;
      if (local_14 < 10000 - *piVar1) {
        piVar3 = &local_14;
      }
      else {
        piVar3 = &local_20;
      }
      local_14 = *piVar3;
      local_24 = 0;
      if (*piVar3 < 1) {
        piVar3 = &local_24;
      }
      else {
        piVar3 = &local_14;
      }
      local_14 = *piVar3;
      if (local_14 == 0) goto LAB_00472bb5;
      iVar2 = *(short *)(param_1 + 0xada) * local_14;
      local_8 = local_8 + iVar2;
      param_4 = param_4 - local_14;
      if (param_5 == 0) {
        piVar3 = (int *)(*(int *)(param_1 + 0xad6) + 0xa7e + param_3 * 4);
        *piVar3 = *piVar3 + local_14;
      }
      else {
        *piVar1 = *piVar1 + local_14;
        piVar3 = (int *)(*(int *)(param_1 + 0xad6) + 0x3a + param_3 * 4);
        *piVar3 = *piVar3 - local_14;
        (&DAT_0059f16c)[param_2 * 0xb6] = (&DAT_0059f16c)[param_2 * 0xb6] - iVar2;
        FUN_00471a98(param_1,*(undefined4 *)(param_1 + 0xad6),param_3,local_14,iVar2);
      }
    }
  } while( true );
}

