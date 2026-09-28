// FUN_004aa20c @ 004aa20c size=303 sig=undefined FUN_004aa20c() cc=unknown
// callers: fread
// callees: FUN_004aa618,memcpy,FUN_004ac2cc,FUN_004aa630

uint FUN_004aa20c(undefined1 *param_1,uint param_2,int *param_3)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined1 *local_c;
  uint local_8;
  
  local_c = param_1;
  if (param_3[3] != 0) {
LAB_004aa22b:
    if (param_2 == 0) {
      return 0;
    }
    do {
      uVar3 = param_3[2];
      if (uVar3 != 0) {
        uVar5 = param_2;
        if (uVar3 < param_2) {
          uVar5 = uVar3;
        }
        memcpy(local_c,*param_3,uVar5);
        *param_3 = *param_3 + uVar5;
        param_3[2] = param_3[2] - uVar5;
        if (param_2 == uVar5) {
          return 0;
        }
        local_c = local_c + uVar5;
        param_2 = param_2 - uVar5;
      }
      if ((uint)param_3[3] <= param_2) {
        uVar5 = param_2 - param_2 % (uint)param_3[3];
        uVar3 = FUN_004ac2cc((int)*(char *)((int)param_3 + 0x16),local_c,uVar5);
        if (param_2 == uVar3) {
          return 0;
        }
        if (uVar3 == 0xffffffff) {
          *(ushort *)((int)param_3 + 0x12) = *(ushort *)((int)param_3 + 0x12) | 0x10;
          return param_2;
        }
        local_c = local_c + uVar3;
        param_2 = param_2 - uVar3;
        if (uVar5 != uVar3) goto code_r0x004aa2b8;
      }
      iVar4 = FUN_004aa630(param_3);
      if (iVar4 == -1) {
        *(ushort *)((int)param_3 + 0x12) = *(ushort *)((int)param_3 + 0x12) | 0x20;
        return param_2;
      }
      local_8._0_1_ = (undefined1)iVar4;
      *local_c = (undefined1)local_8;
      local_c = local_c + 1;
      param_2 = param_2 - 1;
      if (param_2 == 0) {
        return 0;
      }
    } while( true );
  }
  for (; param_2 != 0; param_2 = param_2 - 1) {
    piVar1 = param_3 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 < 0) {
      local_8 = FUN_004aa618(param_3);
    }
    else {
      pbVar2 = (byte *)*param_3;
      *param_3 = *param_3 + 1;
      local_8 = (uint)*pbVar2;
    }
    if (local_8 == 0xffffffff) break;
    *local_c = (undefined1)local_8;
    local_c = local_c + 1;
  }
  if (local_8 == 0xffffffff) {
    *(ushort *)((int)param_3 + 0x12) = *(ushort *)((int)param_3 + 0x12) | 0x20;
  }
  return param_2;
code_r0x004aa2b8:
  if (((*(byte *)((int)param_3 + 0x12) & 0x40) != 0) || (uVar3 == 0)) {
    *(ushort *)((int)param_3 + 0x12) = *(ushort *)((int)param_3 + 0x12) | 0x20;
    return param_2;
  }
  goto LAB_004aa22b;
}

