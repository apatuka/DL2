// FUN_0046bdfc @ 0046bdfc size=937 sig=undefined FUN_0046bdfc() cc=unknown
// callers: FUN_0040d3bc,FUN_0043b1ac,FUN_0046c49c,FUN_004055f8,FUN_004045d0,FUN_004209c0,FUN_00407ad8,FUN_004489e0,FUN_00415624,FUN_0041b608,FUN_0046c1a8
// callees: FUN_0044ba18,FUN_0046adac,FUN_0044eb4c,FUN_004023dc,FUN_0046bce4,FUN_0044d1e4,FUN_0044d230,FUN_0046bd3c,memset

int FUN_0046bdfc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  short local_50 [10];
  int local_3c [4];
  int local_2c;
  int local_28 [5];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(&DAT_0058f150,0,0x2c);
  if (*(char *)(param_1 + 0x20) == -1) {
    DAT_0058f150 = 100;
    DAT_0058f178 = 100;
    local_8 = 100;
  }
  else {
    local_c = (int)(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8];
    if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8] * 2) ==
        0) {
      DAT_0058f150 = 0x50;
    }
    else {
      DAT_0058f150 = (int)*(char *)(param_1 + 0x27);
      iVar2 = 0;
      local_10 = 0;
      piVar3 = (int *)(param_1 + 0x154);
      do {
        iVar1 = *piVar3;
        if ((((iVar1 != 0) && (*(char *)(iVar1 + 4) != '\0')) && ((*(byte *)(iVar1 + 2) & 4) != 0))
           && (((*(byte *)(iVar1 + 2) & 2) != 0 &&
               (local_14 = FUN_004023dc(iVar1,7), local_14 != -1)))) {
          FUN_0044eb4c(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_1,iVar2,local_50,0);
          local_10 = local_10 + local_50[local_14 * 2];
        }
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 0xd;
      } while (iVar2 < 0x24);
      iVar2 = FUN_0046adac(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_1);
      DAT_0058f164 = *(undefined4 *)(&DAT_004d57ec + iVar2 * 4);
      iVar2 = (*(int *)(&DAT_004d5820 + *(char *)(param_1 + 0x21) * 4) *
              (int)*(short *)(&DAT_00559f50 + local_c * 2)) / 100;
      if (iVar2 < *(short *)(param_1 + 0x30)) {
        local_28[4] = ((iVar2 - *(short *)(param_1 + 0x30)) * 0x19) /
                      (int)*(short *)(param_1 + 0x30);
        local_28[3] = 0xffffffec;
        if (local_28[4] < -0x14) {
          piVar3 = local_28 + 3;
        }
        else {
          piVar3 = local_28 + 4;
        }
        DAT_0058f154 = *piVar3;
      }
      else {
        DAT_0058f154 = 0;
      }
      DAT_0058f158 = *(undefined4 *)(&DAT_004d5850 + *(char *)(param_1 + 0x29) * 4);
      iVar2 = FUN_0044d1e4(param_1,0x13,0);
      if (iVar2 == -1) {
        iVar2 = FUN_0046bd3c(param_1);
        DAT_0058f15c = -iVar2;
      }
      else {
        DAT_0058f15c = 0;
      }
      iVar2 = 0;
      local_28[2] = 0;
      do {
        iVar2 = FUN_0044d230(param_1,0xd,iVar2);
        if (iVar2 == -1) break;
        iVar1 = FUN_0044ba18(*(undefined4 *)(param_1 + 0x154 + iVar2 * 0x34));
        local_28[2] = local_28[2] + iVar1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x24);
      DAT_0058f160 = -(*(short *)(&DAT_00559f34 + local_c * 2) * local_28[2]) / 100;
      if (DAT_004d5b08 != 0) {
        DAT_0058f160 = DAT_0058f160 * 2;
      }
      DAT_0058f168 = FUN_0046bce4(param_1);
      local_28[1] = 0x19;
      if (local_10 < 0x1a) {
        piVar3 = &local_10;
      }
      else {
        piVar3 = local_28 + 1;
      }
      DAT_0058f16c = *piVar3;
      local_28[0] = *(int *)(param_1 + 0x62) * 2;
      local_2c = 10;
      if (local_28[0] < 0xb) {
        piVar3 = local_28;
      }
      else {
        piVar3 = &local_2c;
      }
      DAT_0058f170 = *piVar3;
      local_28[2] = 0;
      iVar2 = 0;
      do {
        iVar2 = FUN_0044d230(param_1,0xe,iVar2);
        if (iVar2 == -1) break;
        iVar1 = FUN_0044ba18(*(undefined4 *)(param_1 + 0x154 + iVar2 * 0x34));
        local_28[2] = local_28[2] + iVar1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x24);
      local_3c[3] = (int)DAT_004fa116;
      if (local_28[2] < local_3c[3]) {
        piVar3 = local_28 + 2;
      }
      else {
        piVar3 = local_3c + 3;
      }
      local_28[2] = *piVar3;
      iVar2 = *(int *)(local_3c[3] * 0x2c + 0x4f9bc4 + *piVar3 * 4);
      DAT_0058f174 = iVar2 * 2;
      if (DAT_004d5b08 != 0) {
        DAT_0058f174 = iVar2 << 2;
      }
      DAT_0058f174 = DAT_0058f174 / 100;
    }
    iVar2 = 0;
    piVar3 = &DAT_0058f150;
    do {
      iVar1 = *piVar3;
      piVar3 = piVar3 + 1;
      DAT_0058f178 = DAT_0058f178 + iVar1;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 10);
    local_8 = (int)(short)DAT_0058f178;
    local_3c[2] = 0;
    if ((short)DAT_0058f178 < 1) {
      piVar3 = local_3c + 2;
    }
    else {
      piVar3 = &local_8;
    }
    local_8 = *piVar3;
    local_3c[1] = 100;
    if (*piVar3 < 100) {
      piVar3 = &local_8;
    }
    else {
      piVar3 = local_3c + 1;
    }
    local_8 = *piVar3;
    local_3c[0] = DAT_0058f150 + 10;
    if (*piVar3 < DAT_0058f150 + 10) {
      piVar3 = &local_8;
    }
    else {
      piVar3 = local_3c;
    }
    local_8 = *piVar3;
  }
  return local_8;
}

