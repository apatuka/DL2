// FUN_004931b0 @ 004931b0 size=366 sig=undefined FUN_004931b0() cc=unknown
// callers: FUN_0049e47a
// callees: FUN_00493149,FUN_00492290,FUN_00492b47,FUN_00491b5e

void FUN_004931b0(byte *param_1,int param_2,int param_3,int param_4,int *param_5,int *param_6,
                 undefined1 param_7,byte param_8)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined1 local_24 [4];
  short local_20;
  short local_1e;
  short local_1a;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_00491b5e(local_24);
  iVar1 = 0;
  iVar3 = 0;
  local_10 = 0;
  local_14 = 0;
  if (param_1 != (byte *)0x0) {
    do {
      if ((*param_1 == 0) ||
         (iVar3 = FUN_00492b47(param_1,param_2,param_4,&local_c,&local_8,
                               CONCAT31((int3)((uint)iVar1 >> 8),param_7),&local_14), iVar3 != -1))
      break;
      param_1 = param_1 + local_c;
      param_4 = param_4 - local_c;
      iVar1 = (int)local_1e;
      local_10 = local_10 + local_20 + iVar1;
      local_18 = 0;
      do {
        if ((0x20 < *param_1) || (*param_1 == 0)) goto LAB_0049327e;
        if (*param_1 == 0x20) {
          uVar4 = FUN_00492290(*param_1);
          iVar1 = (int)((ulonglong)uVar4 >> 0x20);
          local_18 = local_18 + (int)uVar4;
        }
        if ((*param_1 == 10) || (*param_1 == 0xd)) {
          if (((*param_1 == 10) && (param_1[1] == 0xd)) || ((*param_1 == 0xd && (param_1[1] == 10)))
             ) {
            param_1 = param_1 + 1;
            param_4 = param_4 + -1;
          }
          param_4 = param_4 + -1;
          goto LAB_0049327e;
        }
        param_1 = param_1 + 1;
        param_4 = param_4 + -1;
      } while (param_4 != 0);
      iVar3 = local_8 + local_18;
      iVar1 = (int)local_1e;
      local_10 = local_10 - (local_20 + iVar1);
LAB_0049327e:
    } while (iVar3 == -1);
  }
  if (iVar3 == -1) {
    local_10 = local_10 - ((int)local_20 + (int)local_1e);
    iVar3 = local_8;
  }
  if ((param_8 & 1) == 0) {
    if ((param_8 & 0x20) != 0) {
      iVar3 = iVar3 + ((param_2 + local_14) - local_8);
    }
  }
  else {
    iVar3 = iVar3 + ((param_2 - local_14) - local_8 >> 1) + local_14;
  }
  if ((param_8 & 8) != 0) {
    iVar1 = FUN_00493149(param_1,param_2,0,0);
    if (iVar1 < 1) {
      iVar1 = 1;
    }
    uVar2 = param_3 - iVar1 * ((int)local_20 + (int)local_1e + (int)local_1a);
    iVar1 = (int)uVar2 >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((uVar2 & 1) != 0);
    }
    local_10 = local_10 + iVar1;
  }
  *param_5 = iVar3;
  *param_6 = local_10;
  return;
}

