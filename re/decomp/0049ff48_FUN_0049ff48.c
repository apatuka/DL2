// FUN_0049ff48 @ 0049ff48 size=550 sig=undefined FUN_0049ff48() cc=unknown
// callers: FUN_004a03cf,FUN_004a016e,FUN_004a060f,FUN_004a034a
// callees: FUN_00491a2b,FUN_0049eb9f,FUN_0049ea99,FUN_00495c6c,FUN_00495cc4,FUN_00491ace,FUN_0049fc69,FUN_00495c51,FUN_0049fca2,FUN_00491efa,FUN_00493108,FUN_00491e02

void FUN_0049ff48(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20 [4];
  uint local_10;
  int local_c;
  int local_8;
  
  local_10 = 0;
  piVar5 = local_20;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *param_2;
    param_2 = param_2 + 1;
    piVar5 = piVar5 + 1;
  }
  if (*(int *)(param_1 + 0x34) == 0) {
    return;
  }
  FUN_00491a2b(0);
  iVar3 = FUN_0049eb9f(param_1,0);
  if (iVar3 == 0) goto LAB_004a0160;
  iVar3 = FUN_0049fc69(param_1);
  if ((*(int *)(param_1 + 0x128) != 0) && (*(int *)(param_1 + 300) != 0)) {
    local_30 = *(int *)(param_1 + 0x120);
    local_2c = *(int *)(param_1 + 0x124);
    if (*(int *)(param_1 + 0x128) == -1) {
      local_28 = local_20[2] - local_20[0];
    }
    else {
      local_28 = *(int *)(param_1 + 0x128);
    }
    local_28 = local_28 + local_30;
    if (*(int *)(param_1 + 300) == -1) {
      local_24 = local_20[3] - local_20[1];
    }
    else {
      local_24 = *(int *)(param_1 + 300);
    }
    local_24 = local_24 + local_2c;
    FUN_00495c51(&local_30,local_20[0],local_20[1]);
    FUN_00495cc4(local_20,&local_30);
    goto LAB_004a00eb;
  }
  FUN_0049fca2(param_1,iVar3,0,0,&local_8,&local_c);
  uVar4 = *(uint *)(param_1 + 0x28) & 0x438000;
  if (uVar4 < 0x28001) {
    if (uVar4 == 0x28000) goto LAB_004a0055;
    if (uVar4 < 0x10001) {
      if (uVar4 == 0x10000) {
        local_10 = 1;
        goto LAB_004a0032;
      }
      if (uVar4 == 0) {
LAB_004a006e:
        local_10 = 1;
      }
      else if (uVar4 == 0x8000) goto LAB_004a0032;
    }
    else {
      if (uVar4 != 0x18000) {
        if (uVar4 == 0x20000) {
          local_20[2] = local_20[2] - (local_8 + 4);
        }
        goto LAB_004a00eb;
      }
LAB_004a0032:
      local_20[1] = local_20[1] + local_c + 4;
    }
  }
  else {
    if (uVar4 == 0x30000) {
      local_10 = 1;
    }
    else if (uVar4 != 0x38000) {
      if (uVar4 == 0x400000) {
        local_20[0] = local_20[0] + local_8 + 4;
      }
      else if (uVar4 == 0x408000) goto LAB_004a006e;
      goto LAB_004a00eb;
    }
LAB_004a0055:
    local_20[3] = local_20[3] - (local_c + 4);
  }
LAB_004a00eb:
  iVar1 = FUN_0049ea99(param_1);
  if (2 < iVar3) {
    iVar3 = iVar3 + -3;
  }
  if ((*(byte *)(param_1 + 0xab + iVar3 * 4) & 0x40) == 0) {
    uVar2 = *(undefined4 *)(param_1 + 0xa8 + iVar3 * 4);
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0xf0 + iVar3 * 4);
  }
  FUN_00491efa(uVar2);
  if ((*(byte *)(param_1 + 0x9f + iVar3 * 4) & 0x40) == 0) {
    uVar2 = *(undefined4 *)(param_1 + 0x9c + iVar3 * 4);
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0xc0 + iVar3 * 4);
  }
  FUN_00491e02(uVar2);
  iVar3 = FUN_00495c6c(local_20);
  if (iVar3 == 0) {
    FUN_00493108(*(undefined4 *)(param_1 + 0x34),local_20,*(uint *)(param_1 + 0x44) | local_10 | 8,0
                );
  }
LAB_004a0160:
  FUN_00491ace();
  return;
}

