// FUN_00453a38 @ 00453a38 size=441 sig=undefined FUN_00453a38() cc=unknown
// callers: FUN_00453ec8,FUN_00454928,FUN_00454690,FUN_00454160,FUN_004543f8
// callees: FUN_00453900,FUN_00450f84,FUN_004480a8,FUN_00453954,FUN_00451180,FUN_00453210

uint FUN_00453a38(int param_1,int param_2)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 local_20;
  undefined4 local_1c;
  short local_16;
  int local_14;
  uint local_10;
  int *local_c;
  int local_8;
  
  local_8 = FUN_00450f84(param_1);
  local_c = (int *)0x0;
  local_10 = 0xffffffff;
  local_14 = 0;
  if (local_8 == 0) {
    local_14 = 1000;
  }
  local_16 = 0;
  bVar1 = *(byte *)(param_1 + 9);
  if (5 < bVar1) {
    local_16 = bVar1 - 5;
  }
  if (bVar1 == 0x17) {
    iVar5 = FUN_00453954(param_1,param_2);
    if (iVar5 != -1) {
      return DAT_0057e244;
    }
    local_16 = 0;
  }
  if ((local_16 == 0xb) && (*(char *)(param_1 + 9) != '\x10')) {
    local_16 = 0;
  }
  for (piVar2 = *(int **)(DAT_0057cdf8 + 0x7c); piVar2 != (int *)0x0;
      piVar2 = *(int **)((int)piVar2 + 0x16)) {
    uVar3 = local_10;
    piVar4 = local_c;
    if ((*(short *)((int)piVar2 + 0xe) < (short)piVar2[5]) &&
       ((((local_16 == 0 || ((int)(char)(&DAT_004f9dc3)[(short)piVar2[1] * 0x32] == (int)local_16))
         && ((short)piVar2[1] != 0x26)) &&
        ((*(char *)(*piVar2 + 5) != '\v' || (*(char *)(param_1 + 9) == '\x10')))))) {
      FUN_00453210(piVar2,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),&local_1c,
                   &local_20);
      uVar6 = FUN_00451180(param_1,local_1c,local_20);
      if (local_8 == 0) {
        if (((param_2 == 0) ||
            (uVar7 = FUN_004480a8(param_1), uVar3 = local_10, piVar4 = local_c, uVar6 <= uVar7)) &&
           ((uVar3 = uVar6, piVar4 = piVar2, local_10 <= uVar6 &&
            ((uVar3 = local_10, piVar4 = local_c, uVar6 == local_10 &&
             (iVar5 = (int)(short)piVar2[5] - (int)*(short *)((int)piVar2 + 0xe), iVar5 < local_14))
            )))) {
          local_14 = iVar5;
          piVar4 = piVar2;
        }
      }
      else {
        iVar5 = FUN_00453900(piVar2);
        uVar3 = local_10;
        piVar4 = local_c;
        if (iVar5 == 0) {
          iVar5 = (int)(short)piVar2[5] - (int)*(short *)((int)piVar2 + 0xe);
          if ((&DAT_004f9dc3)[(short)piVar2[1] * 0x32] == '\n') {
            iVar5 = iVar5 + 0x32;
          }
          if (local_14 < iVar5) {
            local_14 = iVar5;
            uVar3 = uVar6;
            piVar4 = piVar2;
          }
        }
      }
    }
    local_c = piVar4;
    local_10 = uVar3;
  }
  *(int **)(param_1 + 0x40) = local_c;
  DAT_0057e244 = local_10;
  return local_10;
}

