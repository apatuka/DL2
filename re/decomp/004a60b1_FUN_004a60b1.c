// FUN_004a60b1 @ 004a60b1 size=1326 sig=undefined FUN_004a60b1() cc=unknown
// callers: FUN_00414508,FUN_0042ee18,FUN_00423e38,FUN_00427ca0,FUN_00413cd0,FUN_0042d0ac,FUN_0042eaec,FUN_0042e434,FUN_00425f58,FUN_00426868,FUN_0049eb20,FUN_0042a36c,FUN_004a60b1,FUN_0041b1c8,FUN_0043a394,FUN_0043735c,FUN_00414ed0,FUN_00438830,FUN_0041e6d4,FUN_00421904,FUN_004244d4,FUN_0042c204,FUN_00413694,FUN_0048960b,FUN_004272f8,FUN_0043e590,FUN_00416810,FUN_00424f14,FUN_00423104,FUN_0042e6f4,FUN_004197dc,FUN_00428468,FUN_0042df6c,FUN_00435e64,FUN_0042baf8,FUN_0041f384,FUN_00438fe0,FUN_00427fe0,FUN_004288c0,FUN_00494b06,FUN_0043ca24,FUN_00430348,FUN_00416578,FUN_00414ea4
// callees: FUN_00495db5,FUN_0049501c,FUN_004a60b1,FUN_0048f7f1

void FUN_004a60b1(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20 [4];
  int local_10;
  int local_c;
  undefined *local_8;
  
  if (param_1 == 0) {
    piVar5 = &DAT_0069f0fc;
    piVar6 = local_20;
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar6 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    }
  }
  else {
    FUN_0048f7f1(param_1,local_20,0x10);
  }
  if ((((local_20[0] <= DAT_0069f104) && (DAT_0069f0fc <= local_20[2])) &&
      (local_20[1] <= DAT_0069f108)) && (DAT_0069f100 <= local_20[3])) {
    local_20[1] = (local_20[1] - DAT_0069f394) + DAT_0069f0f0;
    local_20[3] = (local_20[3] - DAT_0069f394) + DAT_0069f0f0;
    local_20[0] = (local_20[0] - DAT_0069f398) + DAT_0069f0ec;
    local_20[2] = (local_20[2] - DAT_0069f398) + DAT_0069f0ec;
    if (local_20[1] < DAT_0069f0f0) {
      local_20[1] = DAT_0069f0f0;
    }
    if (DAT_0069f0f8 < local_20[3]) {
      local_20[3] = DAT_0069f0f8;
    }
    if (local_20[0] < DAT_0069f0ec) {
      local_20[0] = DAT_0069f0ec;
    }
    if (DAT_0069f0f4 < local_20[2]) {
      local_20[2] = DAT_0069f0f4;
    }
    if (*(int *)(&DAT_0069f38c + param_2 * 4) == 0) {
      FUN_0048f7f1(local_20,&DAT_0069f10c + param_2 * 0x140,0x10);
      *(int *)(&DAT_0069f38c + param_2 * 4) = *(int *)(&DAT_0069f38c + param_2 * 4) + 1;
    }
    else {
      if (*(int *)(&DAT_0069f38c + param_2 * 4) != 0x14) {
        local_8 = &DAT_0069f10c + param_2 * 0x140;
        local_c = 0;
        do {
          if (*(int *)(&DAT_0069f38c + param_2 * 4) <= local_c) {
LAB_004a6595:
            if (local_c < *(int *)(&DAT_0069f38c + param_2 * 4)) {
              return;
            }
            FUN_0048f7f1(local_20,&DAT_0069f10c +
                                  param_2 * 0x140 + *(int *)(&DAT_0069f38c + param_2 * 4) * 0x10,
                         0x10);
            FUN_0049501c(local_20,0x80ffffff);
            *(int *)(&DAT_0069f38c + param_2 * 4) = *(int *)(&DAT_0069f38c + param_2 * 4) + 1;
            return;
          }
          FUN_0048f7f1(local_8,&local_30,0x10);
          if (((local_28 < local_20[0]) || (local_20[2] < local_30)) ||
             ((local_24 < local_20[1] || (local_20[3] < local_2c)))) goto LAB_004a657e;
          if (local_20[1] < local_2c) {
            iVar1 = local_20[3] - local_2c;
          }
          else {
            iVar1 = local_24 - local_20[1];
          }
          if (local_20[0] < local_30) {
            iVar4 = local_20[2] - local_30;
          }
          else {
            iVar4 = local_28 - local_20[0];
          }
          uVar2 = (local_24 - local_2c) * (local_28 - local_30);
          iVar3 = (int)uVar2 >> 1;
          if (iVar3 < 0) {
            iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
          }
          if (iVar3 <= iVar4 * iVar1) {
LAB_004a6302:
            if (local_2c < local_20[1]) {
              local_20[1] = local_2c;
            }
            if (local_20[3] < local_24) {
              local_20[3] = local_24;
            }
            if (local_30 < local_20[0]) {
              local_20[0] = local_30;
            }
            if (local_20[2] < local_28) {
              local_20[2] = local_28;
            }
            *(int *)(&DAT_0069f38c + param_2 * 4) = *(int *)(&DAT_0069f38c + param_2 * 4) + -1;
            local_c = *(int *)(&DAT_0069f38c + param_2 * 4);
            if (0 < *(int *)(&DAT_0069f38c + param_2 * 4)) {
              FUN_0048f7f1(&DAT_0069f10c + param_2 * 0x140 + local_c * 0x10,local_8,0x10);
            }
            local_20[1] = local_20[1] + DAT_0069f394;
            local_20[0] = local_20[0] + DAT_0069f398;
            local_20[3] = local_20[3] + DAT_0069f394;
            local_20[2] = local_20[2] + DAT_0069f398;
            FUN_004a60b1(local_20,param_2);
            local_c = 0;
            goto LAB_004a6595;
          }
          uVar2 = (local_20[3] - local_20[1]) * (local_20[2] - local_20[0]);
          iVar3 = (int)uVar2 >> 1;
          if (iVar3 < 0) {
            iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
          }
          if (iVar3 <= iVar4 * iVar1) goto LAB_004a6302;
          local_10 = 0;
          iVar1 = FUN_00495db5(&local_30,local_20[0],local_20[1]);
          if ((iVar1 == 0) || (iVar1 = FUN_00495db5(&local_30,local_20[2],local_20[1]), iVar1 == 0))
          {
            iVar1 = FUN_00495db5(&local_30,local_20[2],local_20[1]);
            if ((iVar1 != 0) &&
               (iVar1 = FUN_00495db5(&local_30,local_20[2],local_20[3]), iVar1 != 0)) {
              local_20[2] = local_30;
              if (local_30 <= local_20[0]) {
                return;
              }
              goto LAB_004a657e;
            }
            iVar1 = FUN_00495db5(&local_30,local_20[0],local_20[3]);
            if ((iVar1 != 0) &&
               (iVar1 = FUN_00495db5(&local_30,local_20[2],local_20[3]), iVar1 != 0)) {
              local_20[3] = local_2c;
              if (local_2c <= local_20[1]) {
                return;
              }
              goto LAB_004a657e;
            }
            iVar1 = FUN_00495db5(&local_30,local_20[0],local_20[1]);
            if ((iVar1 != 0) &&
               (iVar1 = FUN_00495db5(&local_30,local_20[0],local_20[3]), iVar1 != 0)) {
              local_20[0] = local_28;
              if (local_20[2] <= local_28) {
                return;
              }
              goto LAB_004a657e;
            }
            iVar1 = FUN_00495db5(local_20,local_30,local_2c);
            if ((iVar1 != 0) &&
               ((iVar1 = FUN_00495db5(local_20,local_28,local_2c), iVar1 != 0 &&
                (local_2c = local_20[3], local_24 <= local_20[3])))) {
              local_10 = 1;
            }
            iVar1 = FUN_00495db5(local_20,local_28,local_2c);
            if (((iVar1 != 0) && (iVar1 = FUN_00495db5(local_20,local_28,local_24), iVar1 != 0)) &&
               (local_28 = local_20[0], local_20[0] <= local_30)) {
              local_10 = 1;
            }
            iVar1 = FUN_00495db5(local_20,local_30,local_24);
            if (((iVar1 != 0) && (iVar1 = FUN_00495db5(local_20,local_28,local_24), iVar1 != 0)) &&
               (local_24 = local_20[1], local_20[1] <= local_2c)) {
              local_10 = 1;
            }
            iVar1 = FUN_00495db5(local_20,local_30,local_2c);
            if (((iVar1 != 0) && (iVar1 = FUN_00495db5(local_20,local_30,local_24), iVar1 != 0)) &&
               (local_30 = local_20[2], local_28 <= local_20[2])) {
              local_10 = 1;
            }
            if (local_10 == 0) goto LAB_004a657e;
            FUN_0049501c(local_8,0x80ff0000);
            *(int *)(&DAT_0069f38c + param_2 * 4) = *(int *)(&DAT_0069f38c + param_2 * 4) + -1;
            if (0 < *(int *)(&DAT_0069f38c + param_2 * 4)) {
              FUN_0048f7f1(&DAT_0069f10c +
                           param_2 * 0x140 + *(int *)(&DAT_0069f38c + param_2 * 4) * 0x10,local_8,
                           0x10);
            }
          }
          else {
            local_20[1] = local_24;
            if (local_20[3] <= local_24) {
              return;
            }
LAB_004a657e:
            local_c = local_c + 1;
            local_8 = local_8 + 0x10;
          }
        } while( true );
      }
      *(undefined4 *)(&DAT_0069f38c + param_2 * 4) = 1;
      *(int *)(&DAT_0069f110 + param_2 * 0x140) = DAT_0069f0f0;
      *(int *)(&DAT_0069f10c + param_2 * 0x140) = DAT_0069f0ec;
      *(int *)(&DAT_0069f118 + param_2 * 0x140) = DAT_0069f0f8;
      *(int *)(&DAT_0069f114 + param_2 * 0x140) = DAT_0069f0f4;
    }
  }
  return;
}

