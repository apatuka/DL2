// FUN_0044eb4c @ 0044eb4c size=869 sig=undefined FUN_0044eb4c() cc=unknown
// callers: FUN_0041d2bc,TotalTaskLabor,FUN_004483d0,FUN_0046bdfc,FUN_0044f3f0,FUN_0041ccb0,TotalUnitLabor,FUN_0041db10,FUN_00403970
// callees: FUN_0044e9e4,FUN_0044ba40,FUN_0044e600,FUN_0046b0e4

void FUN_0044eb4c(byte *param_1,int param_2,int param_3,int *param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  short *local_50;
  int *local_48;
  char *local_44;
  undefined *local_40;
  int local_3c;
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
  
  iVar2 = param_3 * 0x34 + param_2;
  local_8 = iVar2 + 0x140;
  iVar2 = *(int *)(iVar2 + 0x154);
  if (iVar2 != 0) {
    if (((*(byte *)(iVar2 + 2) & 4) == 0) && (param_5 == 0)) {
      iVar2 = 0;
      do {
        iVar2 = iVar2 + 1;
        *param_4 = 0;
        param_4 = param_4 + 1;
      } while (iVar2 < 5);
    }
    else {
      bVar1 = param_1[2];
      iVar6 = (int)*(char *)(iVar2 + 4);
      local_c = iVar6;
      local_10 = 0;
      local_50 = (short *)(&DAT_004f9dca + iVar6 * 0x32);
      local_48 = (int *)(iVar2 + 0x18);
      local_44 = (char *)(iVar2 + 0x2c);
      local_40 = &DAT_004f9dbc;
      piVar8 = param_4;
      do {
        local_14 = 0;
        if ((local_10 == 1) && ((local_c == 0x2e || (local_c == 0x2f)))) {
          iVar3 = FUN_0044e600(iVar2,1);
        }
        else if (param_5 == 0) {
          iVar3 = (int)*local_44;
        }
        else {
          iVar3 = (int)(char)local_40[*(char *)(iVar2 + 4) * 0x32 + 0x18];
        }
        if (iVar3 != 0) {
          local_1c = 100;
          if (param_5 == 0) {
            local_18 = *local_48;
            if (((&DAT_004f9dc8)[iVar6 * 0x32] != '\0') && (*(short *)(iVar2 + 0x14) == 0)) {
              local_1c = (*(char *)(param_2 + 0x35) * 100) / 100;
            }
          }
          else {
            local_20 = FUN_0046b0e4(param_2);
            local_24 = (int)(char)(&DAT_004f9dc4)[*(char *)(iVar2 + 4) * 0x32];
            if ((char)(&DAT_004f9dc4)[*(char *)(iVar2 + 4) * 0x32] < local_20) {
              piVar5 = &local_24;
            }
            else {
              piVar5 = &local_20;
            }
            local_18 = *piVar5;
          }
          if ((local_10 == 1) && ((local_c == 0x2e || (local_c == 0x2f)))) {
            local_28 = FUN_0044e600(iVar2,0);
          }
          else {
            local_28 = (int)*local_50;
          }
          local_2c = 10;
          local_30 = FUN_0044ba40(iVar2);
          if (local_30 < local_2c) {
            piVar5 = &local_30;
          }
          else {
            piVar5 = &local_2c;
          }
          local_34 = 10;
          if (local_18 < 10) {
            piVar7 = &local_18;
          }
          else {
            piVar7 = &local_34;
          }
          local_14 = (*(int *)(*piVar5 * 0x2c + 0x4f9bc4 + *piVar7 * 4) * local_1c *
                      (int)(short)(&DAT_00559e00)[(int)(char)bVar1 + iVar3 * 7] * local_28) / 100000
          ;
        }
        if (*(char *)(iVar2 + 5) == '\v') {
          local_14 = local_14 * 2;
        }
        if ((*(char *)(iVar2 + 5) == '\v') && ((1 << (*param_1 & 0x1f) & (int)DAT_004fc21e) != 0)) {
          local_14 = local_14 * 2;
        }
        if ((((iVar3 == 4) || (iVar3 == 3)) || (iVar3 == 0xd)) || ((iVar3 == 0xc || (iVar3 == 0xf)))
           ) {
          local_14 = local_14 / 10;
          local_38 = (int)(char)(&DAT_004f9dc5)[*(char *)(iVar2 + 4) * 0x32];
          iVar4 = FUN_0044e9e4(param_2,local_8,iVar3,local_14,local_38);
          *piVar8 = iVar4;
          if ((iVar3 == 0xc) || (iVar3 == 0xd)) {
            *piVar8 = *piVar8 + (int)(short)(((int)*(char *)(param_2 + 0x994) * *piVar8) / 100);
          }
          if ((iVar3 == 0xc) && ((*(byte *)(param_2 + 0x1c) & 0x40) != 0)) {
            *piVar8 = *piVar8 / 2;
          }
        }
        else {
          local_14 = (local_14 + 9) / 10;
          *piVar8 = local_14;
          if (((DAT_004d5b08 != 0) && (iVar3 != 7)) && (iVar3 != 5)) {
            *piVar8 = *piVar8 * 2;
          }
        }
        if (local_18 != 0) {
          local_3c = 1;
          piVar5 = param_4 + local_10;
          if (*piVar5 < 2) {
            piVar5 = &local_3c;
          }
          *piVar8 = *piVar5;
        }
        local_10 = local_10 + 1;
        piVar8 = piVar8 + 1;
        local_50 = local_50 + 1;
        local_48 = local_48 + 1;
        local_44 = local_44 + 1;
        local_40 = local_40 + 1;
      } while (local_10 < 5);
    }
  }
  return;
}

