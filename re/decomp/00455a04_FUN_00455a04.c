// FUN_00455a04 @ 00455a04 size=642 sig=undefined FUN_00455a04() cc=unknown
// callers: FUN_00455c88
// callees: FUN_00450e48,FUN_00450f84,FUN_00450efc,FUN_004480a8,FUN_00450da4,FUN_00450e88,FUN_00450ec8,FUN_00448118,FUN_00450f38,FUN_004481a4,FUN_00448210,FUN_00450e28

bool FUN_00455a04(int param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar2 = FUN_00448118(param_1);
  uVar3 = FUN_004480a8(param_1);
  iVar4 = FUN_00450e88(param_1);
  if ((iVar4 != 0) && (*(char *)(DAT_0057cdf8 + 0x15 + (uint)*(byte *)(param_1 + 0x1e)) != '\0')) {
    uVar2 = uVar2 + 0xf;
    uVar3 = uVar3 + 2;
  }
  if (((DAT_0057e244 == 0) && (*(int *)(param_1 + 0x3c) != 0)) &&
     ((((iVar4 = FUN_00450e48(param_1), iVar4 != 0 &&
        (iVar4 = FUN_00450e48(*(undefined4 *)(param_1 + 0x3c)), iVar4 != 0)) ||
       ((iVar4 = FUN_00450e88(param_1), iVar4 != 0 &&
        (iVar4 = FUN_00450e88(*(undefined4 *)(param_1 + 0x3c)), iVar4 != 0)))) ||
      ((iVar4 = FUN_00450ec8(param_1), iVar4 != 0 &&
       (iVar4 = FUN_00450ec8(*(undefined4 *)(param_1 + 0x3c)), iVar4 != 0)))))) {
    uVar2 = uVar2 + 0x19;
  }
  else if ((DAT_0057e244 < 6) && (5 < uVar3)) {
    uVar2 = uVar2 + 10;
  }
  else if (uVar3 < DAT_0057e244) {
    return false;
  }
  iVar4 = FUN_00450e48(param_1);
  if (((iVar4 != 0) && (*(int *)(param_1 + 4) != 0x17)) &&
     (*(char *)(DAT_0057cdf8 + 0xe + (uint)*(byte *)(param_1 + 0x1e)) != '\0')) {
    uVar2 = uVar2 + 0xf;
  }
  iVar4 = FUN_00450ec8(param_1);
  if ((iVar4 != 0) && (*(char *)(DAT_0057cdf8 + 0x1c + (uint)*(byte *)(param_1 + 0x1e)) != '\0')) {
    uVar2 = uVar2 + 0xf;
  }
  iVar4 = FUN_00450efc(param_1);
  if (iVar4 != 0) {
    uVar2 = uVar2 + 0xf;
  }
  iVar4 = FUN_00448210(param_1);
  if (iVar4 != 0) {
    iVar4 = FUN_00450f38(param_1);
    if (iVar4 != 0) {
      uVar2 = uVar2 + 10;
    }
    iVar4 = FUN_00450f38(*(undefined4 *)(param_1 + 0x3c));
    if (iVar4 != 0) {
      uVar2 = uVar2 - 10;
    }
  }
  iVar4 = FUN_004481a4(param_1);
  if (iVar4 != 0) {
    uVar2 = uVar2 - 0x14;
  }
  if ((*(int *)(param_1 + 0x3c) == 0) ||
     ((&DAT_004faf8d)[*(int *)(*(int *)(param_1 + 0x3c) + 4) * 0x24] != '\x03')) {
    iVar4 = FUN_00450e28(param_1);
    if ((iVar4 == 0) || (*(int *)(param_1 + 0x3c) == 0)) {
      if (((*(int *)(param_1 + 0x3c) != 0) && (*(int *)(*(int *)(param_1 + 0x3c) + 4) == 0x1e)) &&
         (*(int *)(param_1 + 4) != 0x1d)) {
        uVar2 = uVar2 - 0x32;
      }
    }
    else if (((&DAT_004faf87)[*(int *)(*(int *)(param_1 + 0x3c) + 4) * 0x24] == '\x02') ||
            ((&DAT_004faf87)[*(int *)(*(int *)(param_1 + 0x3c) + 4) * 0x24] == '\f')) {
      uVar2 = 0;
    }
    else {
      uVar2 = uVar2 - 0x1e;
    }
  }
  else {
    iVar4 = FUN_00450e28(param_1);
    if (iVar4 == 0) {
      iVar4 = *(int *)(param_1 + 4);
      if (((iVar4 != 2) && ((&DAT_004faf87)[iVar4 * 0x24] != '\x03')) &&
         ((&DAT_004faf87)[iVar4 * 0x24] != '\r')) {
        if (((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') &&
           (iVar4 = FUN_00450f84(*(undefined4 *)(param_1 + 0x3c)), iVar4 != 0)) {
          iVar4 = -0x14;
        }
        else {
          iVar4 = -0x1e;
        }
        uVar2 = uVar2 + iVar4;
        iVar4 = *(int *)(param_1 + 4);
        if ((((iVar4 == 1) || (iVar4 == 0x17)) || (iVar4 == 0x18)) || (iVar4 == 0x19)) {
          uVar2 = uVar2 - 0x14;
        }
      }
    }
    else {
      iVar4 = *(int *)(*(int *)(param_1 + 0x3c) + 4);
      if ((iVar4 == 0x11) || (iVar4 == 0x24)) {
        uVar2 = uVar2 - 10;
      }
      else {
        uVar2 = uVar2 + 10;
      }
    }
  }
  if (uVar2 == 0) {
    bVar1 = false;
  }
  else if (uVar2 < 100) {
    uVar3 = FUN_00450da4(100);
    bVar1 = uVar3 < uVar2;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

