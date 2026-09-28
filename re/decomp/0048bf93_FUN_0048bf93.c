// FUN_0048bf93 @ 0048bf93 size=762 sig=undefined FUN_0048bf93() cc=unknown
// callers: FUN_0048c28d,FUN_004996fb
// callees: FUN_0048f774,FUN_0048bb80,memset,FUN_0048be9b,FUN_0048bc0d

undefined4 FUN_0048bf93(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_2c;
  uint local_28;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  undefined4 local_8;
  
  if (param_4 == 0) {
    param_4 = DAT_0065e5a8;
  }
  if (param_4 == -1) {
    uVar1 = FUN_0048be9b(param_1,param_2,param_3,0xffffffff);
  }
  else if ((DAT_0051bde0 & 0xc) == 4) {
    uVar1 = FUN_0048bc0d(param_1,param_2,param_3,param_4);
  }
  else if ((DAT_0051bde0 & 0xc) == 8) {
    uVar1 = FUN_0048be9b(param_1,param_2,param_3,param_4);
  }
  else if ((DAT_0051bde0 & 0xc) == 0xc) {
    iVar2 = FUN_0048be9b(param_1,param_2,param_3,param_4);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      *(undefined2 *)((int)param_1 + 0x2a) = 3;
      uVar1 = 1;
    }
  }
  else {
    memset(&local_74,0,0x6c);
    local_74 = 0x6c;
    local_70 = 0x1007;
    local_c = DAT_0051bdd8 | 0x40;
    local_68 = param_2;
    local_6c = param_3;
    local_2c = 0x20;
    FUN_0048f774(param_1,0xb0,0);
    if (param_4 == 0x10) {
      if (DAT_0065e590 == 0x10) {
        local_28 = DAT_0065e5a0 != 0 | 0x40;
        local_20 = 0x10;
        local_1c = DAT_0065e594;
        local_18 = DAT_0065e598;
        local_14 = DAT_0065e59c;
        local_10 = DAT_0065e5a0;
        if (((DAT_0065e594 == 0xf800) && (DAT_0065e598 == 0x7e0)) && (DAT_0065e59c == 0x1f)) {
          *(undefined2 *)((int)param_1 + 0x26) = 3;
        }
        else {
          *(undefined2 *)((int)param_1 + 0x26) = 2;
        }
      }
      else {
        local_28 = 0x41;
        local_20 = 0x10;
        local_1c = 0x7c00;
        local_18 = 0x3e0;
        local_14 = 0x1f;
        local_10 = 0x8000;
        *(undefined2 *)((int)param_1 + 0x26) = 2;
      }
    }
    else if (param_4 == 0x18) {
      if (DAT_0065e590 == 0x18) {
        local_28 = DAT_0065e5a0 != 0 | 0x40;
        local_1c = DAT_0065e594;
        local_18 = DAT_0065e598;
        local_14 = DAT_0065e59c;
        local_10 = DAT_0065e5a0;
      }
      else {
        local_28 = 0x41;
        local_1c = 0xff0000;
        local_18 = 0xff00;
        local_14 = 0xff;
        local_10 = -0x1000000;
      }
      local_20 = 0x18;
      *(undefined2 *)((int)param_1 + 0x26) = 4;
    }
    else {
      if (DAT_0065e590 == 8) {
        local_28 = DAT_0065e5a0 != 0 | 0x60;
        local_1c = DAT_0065e594;
        local_18 = DAT_0065e598;
        local_14 = DAT_0065e59c;
        local_10 = DAT_0065e5a0;
      }
      else {
        local_28 = 0x60;
        local_1c = 0xe0;
        local_18 = 0x1c;
        local_14 = 2;
      }
      local_20 = 8;
      *(undefined2 *)((int)param_1 + 0x26) = 1;
    }
    iVar2 = (**(code **)(*DAT_0051b810 + 0x18))(DAT_0051b810,&local_74,&local_8,0);
    if (iVar2 == 0) {
      param_1[1] = param_2;
      param_1[2] = param_3;
      *param_1 = 0;
      param_1[3] = param_4;
      *(undefined2 *)(param_1 + 10) = 0;
      *(undefined2 *)(param_1 + 9) = 0;
      *(undefined2 *)((int)param_1 + 0x2a) = 0;
      param_1[4] = param_2;
      param_1[0x10] = local_8;
      param_1[0xf] = 0;
      FUN_0048bb80(param_1,0);
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

