// FUN_0044eeb4 @ 0044eeb4 size=603 sig=undefined FUN_0044eeb4() cc=unknown
// callers: FUN_004068f8,FUN_004484fc,IsBuildTaskDifferent,FUN_0040854c,FUN_0040552c,FUN_0040668c,FUN_004489e0,FUN_004067d0,FUN_004021e0,FUN_00406538
// callees: FUN_0044e9e4,FUN_0044ba40,FUN_0044e600

int FUN_0044eeb4(byte *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int local_28 [4];
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar5 = 0;
  iVar1 = param_3 * 0x34 + param_2;
  local_8 = iVar1 + 0x140;
  iVar1 = *(int *)(iVar1 + 0x154);
  local_c = (int)(char)param_1[2];
  if ((iVar1 != 0) && ((*(byte *)(iVar1 + 2) & 4) != 0)) {
    local_10 = (int)*(char *)(iVar1 + 4);
    if ((param_4 == 1) && ((local_10 == 0x2e || (local_10 == 0x2f)))) {
      iVar2 = FUN_0044e600(iVar1,1);
    }
    else {
      iVar2 = (int)*(char *)(iVar1 + 0x2c + param_4);
    }
    if (iVar2 != 0) {
      iVar5 = 100;
      if (((&DAT_004f9dc8)[local_10 * 0x32] != '\0') && (*(short *)(iVar1 + 0x14) == 0)) {
        iVar5 = (*(char *)(param_2 + 0x35) * 100) / 100;
      }
      if ((param_4 == 1) && ((local_10 == 0x2e || (local_10 == 0x2f)))) {
        local_14 = FUN_0044e600(iVar1,0);
      }
      else {
        local_14 = (int)*(short *)(&DAT_004f9dca + param_4 * 2 + local_10 * 0x32);
      }
      local_18 = 10;
      local_28[3] = FUN_0044ba40(iVar1);
      if (local_28[3] < local_18) {
        piVar3 = local_28 + 3;
      }
      else {
        piVar3 = &local_18;
      }
      local_28[2] = 10;
      if (param_5 < 10) {
        piVar4 = &param_5;
      }
      else {
        piVar4 = local_28 + 2;
      }
      iVar5 = (*(int *)(*piVar3 * 0x2c + 0x4f9bc4 + *piVar4 * 4) * iVar5 *
               (int)(short)(&DAT_00559e00)[iVar2 * 7 + local_c] * local_14) / 100000;
    }
    if (*(char *)(iVar1 + 5) == '\v') {
      iVar5 = iVar5 * 2;
    }
    if ((*(char *)(iVar1 + 5) == '\v') && ((1 << (*param_1 & 0x1f) & (int)DAT_004fc21e) != 0)) {
      iVar5 = iVar5 * 2;
    }
    if ((((iVar2 == 4) || (iVar2 == 3)) || (iVar2 == 0xd)) || ((iVar2 == 0xc || (iVar2 == 0xf)))) {
      iVar5 = FUN_0044e9e4(param_2,local_8,iVar2,iVar5 / 10,
                           (int)(char)(&DAT_004f9dc5)[*(char *)(iVar1 + 4) * 0x32]);
      if ((iVar2 == 0xc) && ((*(byte *)(param_2 + 0x1c) & 0x40) != 0)) {
        iVar5 = iVar5 / 2;
      }
    }
    else {
      iVar5 = (iVar5 + 9) / 10;
      if ((DAT_004d5b08 != 0) && ((iVar2 != 7 && (iVar2 != 5)))) {
        iVar5 = iVar5 * 2;
      }
    }
    if (param_5 != 0) {
      local_28[1] = 1;
      local_28[0] = iVar5;
      if (iVar5 < 2) {
        piVar3 = local_28 + 1;
      }
      else {
        piVar3 = local_28;
      }
      iVar5 = *piVar3;
    }
  }
  return iVar5;
}

