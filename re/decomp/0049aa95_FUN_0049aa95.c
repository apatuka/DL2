// FUN_0049aa95 @ 0049aa95 size=887 sig=undefined FUN_0049aa95() cc=unknown
// callers: FUN_0047fffc,FUN_0049d7f4,FUN_00458d80,FUN_00459864,FUN_0049fe03,FUN_0049fd2e,FUN_00496e80
// callees: FUN_0049b268,FUN_0048aeb0,FUN_00499840,FUN_0049b1fa,FUN_0048f7f1

void FUN_0049aa95(short *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_1c;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1 != (short *)0x0) {
    if (param_4 == -1) {
      param_4 = (int)param_1[7];
    }
    if ((-1 < param_4) && (param_4 < 8)) {
      param_2 = param_2 - param_1[5];
      param_3 = param_3 - param_1[6];
      if ((DAT_0065e574 <= param_1[2] + param_2) &&
         (((param_2 < DAT_0065e57c && (DAT_0065e570 <= param_1[1] + param_3)) &&
          (param_3 < DAT_0065e578)))) {
        local_c = 0;
        local_8 = 0;
        local_14 = (int)param_1[1];
        iVar3 = (int)param_1[2];
        if (param_2 < DAT_0065e574) {
          local_8 = DAT_0065e574 - param_2;
          iVar3 = iVar3 - local_8;
          param_2 = DAT_0065e574;
        }
        local_10 = local_8;
        if (DAT_0065e57c <= iVar3 + param_2) {
          local_10 = local_8 + ((iVar3 + param_2) - DAT_0065e57c);
          iVar3 = DAT_0065e57c - param_2;
        }
        if (param_3 < DAT_0065e570) {
          local_c = DAT_0065e570 - param_3;
          local_14 = local_14 - local_c;
          param_3 = DAT_0065e570;
        }
        if (DAT_0065e578 <= local_14 + param_3) {
          local_14 = DAT_0065e578 - param_3;
        }
        if ((0 < iVar3) && (0 < local_14)) {
          FUN_00499840(param_2,param_3);
          iVar1 = (int)param_1 +
                  (((int)param_1[4] & 3U) + 1) * local_8 + param_1[3] * local_c + 0x1a;
          if (DAT_0051e35c == 0x100008) {
            if (param_5 == 0) {
              uVar2 = 1;
              if (*(short *)(DAT_0051bddc + 0x26) != 2) {
                uVar2 = 2;
              }
              local_1c = FUN_0049b1fa(param_1,0);
              FUN_0049b268(local_1c,uVar2);
            }
            else {
              local_1c = FUN_0049b1fa(param_1,0);
              if (local_1c != 0) {
                FUN_0048f7f1(local_1c,DAT_0051e21c,*(short *)(local_1c + 2) * 4 + 8);
                uVar2 = 1;
                if (*(short *)(DAT_0051bddc + 0x26) != 2) {
                  uVar2 = 2;
                }
                local_1c = DAT_0051e21c;
                FUN_0049b268(DAT_0051e21c,uVar2);
              }
            }
            if (*param_1 == 2) {
              if (*(int *)(DAT_0069ee98 + param_4 * 4) != 0) {
                (**(code **)(DAT_0069ee98 + param_4 * 4))
                          (iVar1,local_14,iVar3,local_10,local_1c + 8,DAT_0051c3c4,DAT_0051c3c0);
              }
            }
            else if (*param_1 == 1) {
              if (*(int *)(DAT_0069ee94 + param_4 * 4) != 0) {
                (**(code **)(DAT_0069ee94 + param_4 * 4))
                          (iVar1,local_14,iVar3,local_10,local_1c + 8,DAT_0051c3c4,DAT_0051c3c0);
              }
            }
            else if ((*param_1 == 3) && (*(int *)(DAT_0069ee90 + param_4 * 4) != 0)) {
              (**(code **)(DAT_0069ee90 + param_4 * 4))
                        (param_1 + 0xd,local_c,local_8,local_14,iVar3,local_1c + 8,DAT_0051c3c4,
                         DAT_0051c3c0);
            }
          }
          else {
            FUN_0048aeb0(param_1,(int)*(short *)(DAT_0051bddc + 0x26));
            if (*param_1 == 2) {
              if (*(int *)(DAT_0069ee98 + param_4 * 4) != 0) {
                (**(code **)(DAT_0069ee98 + param_4 * 4))
                          (iVar1,local_14,iVar3,local_10,DAT_0051c3c4,DAT_0051c3c0);
              }
            }
            else if (*param_1 == 1) {
              if (DAT_0051e35c == 0x100010) {
                iVar3 = iVar3 * 2;
                local_10 = local_10 * 2;
              }
              if (*(int *)(DAT_0069ee94 + param_4 * 4) != 0) {
                (**(code **)(DAT_0069ee94 + param_4 * 4))
                          (iVar1,local_14,iVar3,local_10,DAT_0051c3c4,DAT_0051c3c0);
              }
            }
            else if ((*param_1 == 3) && (*(int *)(DAT_0069ee90 + param_4 * 4) != 0)) {
              (**(code **)(DAT_0069ee90 + param_4 * 4))
                        (param_1 + 0xd,local_c,local_8,local_14,iVar3,DAT_0051c3c4,DAT_0051c3c0);
            }
          }
        }
      }
    }
  }
  return;
}

