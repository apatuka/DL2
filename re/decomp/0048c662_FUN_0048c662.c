// FUN_0048c662 @ 0048c662 size=508 sig=undefined FUN_0048c662() cc=unknown
// callers: FUN_0048c85e
// callees: FUN_0048f7f1,FUN_0049b268,FUN_0049a72d,FUN_0048c2c5,FUN_0048c3f4,FUN_0048d03e

void FUN_0048c662(int param_1,int param_2,int *param_3,int *param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int local_34 [4];
  int local_24 [4];
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  piVar4 = local_24;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = *param_3;
    param_3 = param_3 + 1;
    piVar4 = piVar4 + 1;
  }
  piVar4 = local_34;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = *param_4;
    param_4 = param_4 + 1;
    piVar4 = piVar4 + 1;
  }
  if (local_24[3] - local_24[1] < local_34[3] - local_34[1]) {
    local_8 = local_24[3] - local_24[1];
  }
  else {
    local_8 = local_34[3] - local_34[1];
  }
  if (local_24[2] - local_24[0] < local_34[2] - local_34[0]) {
    iVar3 = local_24[2] - local_24[0];
  }
  else {
    iVar3 = local_34[2] - local_34[0];
  }
  if ((((0 < iVar3) && (0 < local_8)) && (*(int *)(param_1 + 0xc) != -1)) &&
     (*(int *)(param_2 + 0xc) != -1)) {
    local_24[2] = local_24[0] + iVar3;
    local_24[3] = local_24[1] + local_8;
    local_34[2] = local_34[0] + iVar3;
    local_34[3] = local_34[1] + local_8;
    iVar1 = FUN_0048c2c5(param_2);
    if (iVar1 != 0) {
      local_14 = FUN_0048d03e(param_2,local_34[0],local_34[1]);
      iVar1 = FUN_0048c2c5(param_1);
      if (iVar1 != 0) {
        local_10 = FUN_0048d03e(param_1,local_24[0],local_24[1]);
        local_c = FUN_0049a72d(*(int *)(param_2 + 0xc) << 0x10 | *(uint *)(param_1 + 0xc));
        if (local_c == 1) {
          if (*(int *)(param_1 + 0x3c) != 0) {
            FUN_0048f7f1(**(undefined4 **)(param_1 + 0x3c),DAT_0051e21c,
                         *(short *)(**(int **)(param_1 + 0x3c) + 2) * 4 + 8);
            uVar2 = 1;
            if (*(short *)(param_2 + 0x26) != 2) {
              uVar2 = 2;
            }
            FUN_0049b268(DAT_0051e21c,uVar2);
          }
          if ((&PTR_FUN_0051e290)[local_c * 8 + param_5] != (undefined *)0x0) {
            (*(code *)(&PTR_FUN_0051e290)[param_5 * 8])
                      (local_10,local_8,iVar3,*(int *)(param_1 + 0x10) - iVar3,DAT_0051e21c + 8,
                       local_14,*(undefined4 *)(param_2 + 0x10));
          }
        }
        else if ((&PTR_FUN_0051e290)[local_c * 8 + param_5] != (undefined *)0x0) {
          (*(code *)(&PTR_FUN_0051e290)[local_c * 8 + param_5])
                    (local_10,local_8,(*(int *)(param_1 + 0xc) + 7 >> 3) * iVar3,
                     *(int *)(param_1 + 0x10) - (*(int *)(param_1 + 0xc) + 7 >> 3) * iVar3,local_14,
                     *(undefined4 *)(param_2 + 0x10));
        }
        FUN_0048c3f4(param_1);
      }
      FUN_0048c3f4(param_2);
    }
  }
  return;
}

