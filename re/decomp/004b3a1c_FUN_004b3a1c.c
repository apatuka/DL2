// FUN_004b3a1c @ 004b3a1c size=374 sig=undefined FUN_004b3a1c() cc=unknown
// callers: FUN_004b3dbc
// callees: FUN_004b3908

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004b3a1c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_8;
  
  if ((param_1 < 0x46) || (0x8a < param_1)) {
    local_8 = -1;
  }
  else {
    param_5 = param_5 + param_6 / 0x3c;
    param_4 = param_4 + param_5 / 0x3c;
    param_3 = param_3 + param_4 / 0x18;
    param_4 = param_4 % 0x18;
    uVar5 = param_1 + param_2 / 0xc;
    pcVar1 = &DAT_00521944 + param_2 % 0xc;
    iVar3 = param_2 % 0xc;
    while (iVar4 = iVar3, pcVar2 = pcVar1, *pcVar2 <= param_3) {
      if (((uVar5 & 3) == 0) && (iVar4 == 1)) {
        if (param_3 < 0x1d) break;
        iVar3 = -0x1d;
      }
      else {
        iVar3 = -(int)*pcVar2;
      }
      param_3 = param_3 + iVar3;
      pcVar1 = pcVar2 + 1;
      iVar3 = iVar4 + 1;
      if (0xb < iVar4 + 1) {
        uVar5 = uVar5 + 1;
        pcVar1 = pcVar2 + -0xb;
        iVar3 = iVar4 + -0xb;
      }
    }
    iVar3 = uVar5 - 0x44;
    if (iVar3 < 0) {
      iVar3 = uVar5 - 0x41;
    }
    iVar3 = iVar3 >> 2;
    if (((uVar5 & 3) == 0) && (iVar4 < 2)) {
      iVar3 = iVar3 + -1;
    }
    local_8 = (iVar3 + (uVar5 - 0x46) * 0x16d + (&DAT_00521950)[iVar4] + param_3) * 0x15180 +
              param_4 * 0xe10 + (param_5 % 0x3c) * 0x3c + param_6 % 0x3c + _DAT_00521a68;
    if ((DAT_00521a6c != 0) &&
       (iVar3 = FUN_004b3908(param_4,param_3,iVar4 + 1,uVar5 - 0x46), iVar3 != 0)) {
      local_8 = local_8 + -0xe10;
    }
    if (local_8 < 1) {
      local_8 = -1;
    }
  }
  return local_8;
}

