// FUN_0049ae0c @ 0049ae0c size=1006 sig=undefined FUN_0049ae0c() cc=unknown
// callers: FUN_00496ffb
// callees: FUN_0049b268,FUN_0048aeb0,FUN_0048d03e,FUN_0048bbbb,FUN_0049a72d,FUN_0049b1fa,FUN_004989cf,FUN_0048f7f1,FUN_00498ba9

void FUN_0049ae0c(short *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_2c = 0;
  if ((param_1 != (short *)0x0) && (param_6 != 0)) {
    FUN_0048bbbb(param_6,&local_3c);
    if (param_4 == -1) {
      param_4 = (int)param_1[7];
    }
    if ((-1 < param_4) && (param_4 < 8)) {
      param_2 = param_2 - param_1[5];
      param_3 = param_3 - param_1[6];
      if ((local_3c <= param_1[2] + param_2) &&
         (((param_2 < local_34 && (local_38 <= param_1[1] + param_3)) && (param_3 < local_30)))) {
        local_c = 0;
        local_8 = 0;
        local_14 = (int)param_1[1];
        local_18 = (int)param_1[2];
        if (param_2 < local_3c) {
          local_8 = DAT_0065e574 - param_2;
          local_18 = local_18 - local_8;
          param_2 = local_3c;
        }
        local_10 = local_8;
        if (local_34 <= param_2 + local_18) {
          local_10 = local_8 + ((param_2 + local_18) - local_34);
          local_18 = local_34 - param_2;
        }
        if (param_3 < local_38) {
          local_c = local_38 - param_3;
          local_14 = local_14 - local_c;
          param_3 = local_38;
        }
        if (local_30 <= param_3 + local_14) {
          local_14 = local_30 - param_3;
        }
        if ((0 < local_18) && (0 < local_14)) {
          local_1c = FUN_0049a72d(*(int *)(param_6 + 0xc) << 0x10 | (((int)param_1[4] & 3U) + 1) * 8
                                 );
          local_24 = FUN_0048d03e(param_6,param_2,param_3);
          local_20 = (int)param_1 +
                     (((int)param_1[4] & 3U) + 1) * local_8 + param_1[3] * local_c + 0x1a;
          if (local_1c == 1) {
            if (param_5 == 0) {
              uVar1 = 1;
              if (*(short *)(param_6 + 0x26) != 2) {
                uVar1 = 2;
              }
              local_28 = FUN_0049b1fa(param_1,0);
              FUN_0049b268(local_28,uVar1);
            }
            else {
              local_28 = FUN_0049b1fa(param_1,0);
              if (local_28 != 0) {
                local_2c = FUN_00498ba9(*(short *)(local_28 + 2) * 4 + 8);
                if (local_2c != 0) {
                  FUN_0048f7f1(local_28,local_2c,*(short *)(local_28 + 2) * 4 + 8);
                  uVar1 = 1;
                  if (*(short *)(param_6 + 0x26) != 2) {
                    uVar1 = 2;
                  }
                  local_28 = local_2c;
                  FUN_0049b268(local_2c,uVar1);
                }
              }
            }
            if (*param_1 == 2) {
              if ((&PTR_LAB_0051e2f0)[local_1c * 8 + param_4] != (undefined *)0x0) {
                (*(code *)(&PTR_LAB_0051e2f0)[local_1c * 8 + param_4])
                          (local_20,local_14,local_18,local_10,local_28 + 8,local_24,
                           *(undefined4 *)(param_6 + 0x10));
              }
            }
            else if (*param_1 == 1) {
              if ((&PTR_FUN_0051e290)[local_1c * 8 + param_4] != (undefined *)0x0) {
                (*(code *)(&PTR_FUN_0051e290)[local_1c * 8 + param_4])
                          (local_20,local_14,local_18,local_10,local_28 + 8,local_24,
                           *(undefined4 *)(param_6 + 0x10));
              }
            }
            else if ((*param_1 == 3) &&
                    ((&PTR_LAB_0051e230)[local_1c * 8 + param_4] != (undefined *)0x0)) {
              (*(code *)(&PTR_LAB_0051e230)[local_1c * 8 + param_4])
                        (param_1 + 0xd,local_c,local_8,local_14,local_18,local_28 + 8,local_24,
                         *(undefined4 *)(param_6 + 0x10));
            }
          }
          else {
            FUN_0048aeb0(param_1,(int)*(short *)(param_6 + 0x26));
            if (*param_1 == 2) {
              if ((&PTR_LAB_0051e2f0)[local_1c * 8 + param_4] != (undefined *)0x0) {
                (*(code *)(&PTR_LAB_0051e2f0)[local_1c * 8 + param_4])
                          (local_20,local_14,local_18,local_10,local_24,
                           *(undefined4 *)(param_6 + 0x10));
              }
            }
            else if (*param_1 == 1) {
              if (local_1c == 2) {
                local_18 = local_18 * 2;
                local_10 = local_10 * 2;
              }
              if ((&PTR_FUN_0051e290)[local_1c * 8 + param_4] != (undefined *)0x0) {
                (*(code *)(&PTR_FUN_0051e290)[local_1c * 8 + param_4])
                          (local_20,local_14,local_18,local_10,local_24,
                           *(undefined4 *)(param_6 + 0x10));
              }
            }
            else if ((*param_1 == 3) &&
                    ((&PTR_LAB_0051e230)[local_1c * 8 + param_4] != (undefined *)0x0)) {
              (*(code *)(&PTR_LAB_0051e230)[local_1c * 8 + param_4])
                        (param_1 + 0xd,local_c,local_8,local_14,local_18,local_24,
                         *(undefined4 *)(param_6 + 0x10));
            }
          }
          if (local_2c != 0) {
            FUN_004989cf(local_2c);
          }
        }
      }
    }
  }
  return;
}

