// FUN_00402548 @ 00402548 size=1835 sig=undefined FUN_00402548() cc=unknown
// callers: FUN_00402cc0,FUN_00402df4,FUN_00402d58,FUN_0040dd80
// callees: FUN_0044d600,FUN_0044ba40,FUN_00409270,FUN_00401718,FUN_0046c3fc,FUN_0044e9e4

int FUN_00402548(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int local_d0 [36];
  int *local_40;
  undefined1 local_3c [4];
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = -1000000;
  local_14 = -1;
  local_18 = (int)(char)(&DAT_004f9dc3)[param_2 * 0x32];
  iVar4 = (int)(char)(&DAT_004f9dc5)[param_2 * 0x32];
  local_20 = 0;
  FUN_00401718(param_1,local_d0);
  local_8 = 0;
  local_40 = &DAT_004c5e58;
  do {
    iVar3 = *local_40;
    iVar1 = FUN_0044d600(param_1,param_2,iVar3);
    if (iVar1 == 0) {
      local_24 = FUN_0044e9e4(param_1,iVar3 * 0x34 + param_1 + 0x140,0xc,100,iVar4);
      local_28 = FUN_0044e9e4(param_1,iVar3 * 0x34 + param_1 + 0x140,0xd,100,iVar4);
      local_2c = FUN_0044e9e4(param_1,iVar3 * 0x34 + param_1 + 0x140,0xf,100,iVar4);
      local_30 = FUN_0044e9e4(param_1,iVar3 * 0x34 + param_1 + 0x140,3,100,iVar4);
      local_34 = FUN_0044e9e4(param_1,iVar3 * 0x34 + param_1 + 0x140,4,100,iVar4);
      local_34 = local_34 * 4;
      switch(local_18) {
      default:
        local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                          local_30 * local_30 + local_34 * local_34);
        local_c = local_c + local_d0[iVar3] * -0x32;
        break;
      case 1:
        if (param_3 == 0xd) {
          uVar2 = local_2c * local_2c + local_30 * local_30 + local_34 * local_34;
          local_c = (int)uVar2 >> 1;
          if (local_c < 0) {
            local_c = local_c + (uint)((uVar2 & 1) != 0);
          }
          local_c = (local_28 * local_28 + local_24) - local_c;
          local_1c = local_28;
        }
        else {
          uVar2 = local_2c * local_2c + local_30 * local_30 + local_34 * local_34;
          local_c = (int)uVar2 >> 1;
          if (local_c < 0) {
            local_c = local_c + (uint)((uVar2 & 1) != 0);
          }
          local_c = (local_24 * local_24 + local_28) - local_c;
          local_1c = local_24;
        }
        break;
      case 2:
        if (param_3 == 4) {
          uVar2 = local_2c * local_2c + local_24 * local_24 + local_28 * local_28;
          local_c = (int)uVar2 >> 1;
          if (local_c < 0) {
            local_c = local_c + (uint)((uVar2 & 1) != 0);
          }
          local_c = (local_34 * local_34 + local_30) - local_c;
          local_1c = local_34;
        }
        else {
          uVar2 = local_2c * local_2c + local_24 * local_24 + local_28 * local_28;
          local_c = (int)uVar2 >> 1;
          if (local_c < 0) {
            local_c = local_c + (uint)((uVar2 & 1) != 0);
          }
          local_c = (local_30 * local_30 + local_34) - local_c;
          local_1c = local_30;
        }
        break;
      case 3:
        uVar2 = local_24 * local_24 + local_28 * local_28 + local_30 * local_30 +
                local_34 * local_34;
        iVar1 = (int)uVar2 >> 1;
        if (iVar1 < 0) {
          iVar1 = iVar1 + (uint)((uVar2 & 1) != 0);
        }
        local_c = (local_2c * local_2c - iVar1) + *(short *)(param_1 + 0x9c0) * 100;
        local_1c = local_2c;
        break;
      case 4:
        iVar1 = *(short *)(param_1 + 0x9ba) * 1000;
        local_c = iVar1 + 5000;
        if (*(char *)(param_1 + 0x21) == '\x04') {
          local_c = iVar1 + 0x157c;
        }
        local_c = local_c - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                             local_30 * local_30 + local_34 * local_34);
        local_c = local_c + local_d0[iVar3] * -0x32;
        break;
      case 5:
        if (*(short *)(param_1 + 0x9c0) < 2) {
          if (*(short *)(param_1 + 0x9bc) == 0) {
            local_c = 0;
          }
          else {
            local_c = (*(short *)(param_1 + 0x9bc) * 1000 >>
                      ((byte)*(undefined2 *)(param_1 + 0x9c0) & 0x1f)) + 5000;
          }
          if (*(char *)(param_1 + 0x21) == '\x03') {
            local_c = local_c + 500;
          }
          local_c = local_c - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                               local_30 * local_30 + local_34 * local_34);
          local_c = local_c + local_d0[iVar3] * -0x32;
        }
        else {
          local_c = -1000000;
        }
        break;
      case 6:
        if (*(short *)(param_1 + 0x9c2) == 0) {
          local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                            local_30 * local_30 + local_34 * local_34);
          local_c = local_c + local_d0[iVar3] * -0x32;
        }
        else {
          local_c = -1000000;
        }
        break;
      case 7:
        uVar2 = 1 << ((byte)param_3 & 0x1f);
        if (((uVar2 & *(uint *)(param_1 + 0x8a4)) == 0) &&
           ((uVar2 & *(uint *)(param_1 + 0x8a0)) == 0)) {
          local_c = -1000000;
        }
        else {
          local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                            local_30 * local_30 + local_34 * local_34);
          local_c = local_c + local_d0[iVar3] * -0x32;
          if (*(char *)(param_1 + 0x21) == '\x03') {
            local_c = local_c + -500;
          }
          if (*(char *)(param_1 + 0x21) == '\x04') {
            local_c = local_c + -0xfa;
          }
        }
        break;
      case 8:
        local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                          local_30 * local_30 + local_34 * local_34);
        local_c = local_c + local_d0[iVar3] * -0x32;
        if (*(char *)(param_1 + 0x21) == '\x03') {
          local_c = local_c + -500;
        }
        if (*(char *)(param_1 + 0x21) == '\x04') {
          local_c = local_c + -0xfa;
        }
        break;
      case 10:
        if (*(short *)(param_1 + 0x9ca) == 0) {
          local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                            local_30 * local_30 + local_34 * local_34);
          local_c = local_c + local_d0[iVar3] * -0x32;
        }
        else {
          local_c = -1000000;
        }
        break;
      case 0xd:
        if (*(short *)(param_1 + 0x9d0) == 0) {
          local_c = 5000 - (local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                            local_30 * local_30 + local_34 * local_34);
          local_c = local_c + local_d0[iVar3] * -0x32;
        }
        else {
          local_c = -1000000;
        }
        break;
      case 0x12:
        iVar1 = FUN_00409270((int)*(char *)(param_1 + 0x20),param_1);
        if (*(short *)(param_1 + 0x9da) < iVar1) {
          local_c = -(local_2c * local_2c + local_24 * local_24 + local_28 * local_28 +
                      local_30 * local_30 + local_34 * local_34);
          if (param_2 == 0x1e) {
            local_c = local_c + local_d0[iVar3] * -100;
          }
          else {
            local_c = local_c + local_d0[iVar3] * 100;
          }
        }
        else {
          local_c = -1000000;
        }
      }
      if ((local_10 < local_c) || (local_14 == -1)) {
        local_10 = local_c;
        local_20 = local_1c;
        local_14 = iVar3;
      }
    }
    local_8 = local_8 + 1;
    local_40 = local_40 + 1;
  } while (local_8 < 0x24);
  *param_4 = local_14;
  *param_5 = local_20;
  if (local_10 != -1000000) {
    iVar4 = 0;
    FUN_0046c3fc(param_1,&local_38,local_3c);
    local_40 = (int *)(param_1 + 0x154);
    local_8 = 0;
    do {
      iVar3 = *local_40;
      if (((iVar3 != 0) && (*(char *)(iVar3 + 4) != '\0')) && (*(char *)(iVar3 + 5) != '\x11')) {
        iVar3 = FUN_0044ba40(iVar3);
        iVar4 = iVar4 + iVar3;
      }
      local_8 = local_8 + 1;
      local_40 = local_40 + 0xd;
    } while (local_8 < 0x24);
    local_10 = local_10 + (local_38 - iVar4) * 100;
  }
  return local_10;
}

