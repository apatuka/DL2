// FUN_004865e8 @ 004865e8 size=274 sig=undefined FUN_004865e8() cc=unknown
// callers: FUN_00486734,FUN_00486860
// callees: FUN_0046ca40,FUN_004867d8

void FUN_004865e8(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = param_1[1];
  uVar3 = (uint)*(char *)(DAT_00657de0 + 0x150 + *param_1 * 0x34);
  if (iVar4 == 2) {
    if ((uVar3 & 1) != 0) {
      uVar3 = uVar3 | 0x10;
    }
    uVar3 = (int)uVar3 >> 1;
  }
  else if (iVar4 == 4) {
    if ((uVar3 & 1) != 0) {
      uVar3 = uVar3 | 0x10;
    }
    if ((uVar3 & 2) != 0) {
      uVar3 = uVar3 | 0x20;
    }
    uVar3 = (int)uVar3 >> 2;
  }
  else if (iVar4 == 8) {
    uVar3 = uVar3 * 2;
    if ((uVar3 & 0x10) != 0) {
      uVar3 = uVar3 | 1;
    }
    uVar3 = uVar3 & 0xf;
  }
  uVar2 = FUN_0046ca40();
  iVar1 = *(int *)(&DAT_005124e8 + (uVar2 % 6) * 4 + uVar3 * 0x18);
  if (iVar1 == 1) {
    if (iVar4 == 1) {
      iVar4 = 8;
    }
    else {
      iVar4 = iVar4 >> 1;
    }
  }
  else if (iVar1 == 2) {
    if (iVar4 == 8) {
      iVar4 = 1;
    }
    else {
      iVar4 = iVar4 * 2;
    }
  }
  else if (iVar1 == 3) {
    if (iVar4 == 1) {
      iVar4 = 4;
    }
    else if (iVar4 == 2) {
      iVar4 = 8;
    }
    else {
      iVar4 = iVar4 >> 2;
    }
  }
  FUN_004867d8((*param_1 % 6) * 3 + param_1[2],(*param_1 / 6) * 3 + param_1[3],iVar4,param_1[4],
               param_1[6]);
  param_1[1] = iVar4;
  return;
}

