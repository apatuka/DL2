// FUN_0049ebfb @ 0049ebfb size=439 sig=undefined FUN_0049ebfb() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049117e,FUN_0049ea99,FUN_0049eb44,FUN_00491a2b,FUN_0049eb9f,FUN_00495cc4,FUN_00491ace,FUN_0049f09b,FUN_004921f8

undefined4 FUN_0049ebfb(int param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x1c) == 4) {
    FUN_00491a2b(0);
    iVar1 = FUN_0049eb9f(param_1,DAT_0051e380);
    if (iVar1 != 0) {
      if (*(int *)(param_1 + 0x88) < 1) {
        for (local_14 = 0; local_14 < *(int *)(param_1 + 0x8c); local_14 = local_14 + 1) {
          uVar2 = FUN_0049117e(*(undefined4 *)(param_1 + 0x50),0,local_14);
          iVar1 = FUN_004921f8(uVar2);
          if (*(int *)(param_1 + 0x88) < iVar1) {
            *(int *)(param_1 + 0x88) = iVar1;
          }
        }
        *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 8;
      }
      *param_3 = 0;
      param_3[2] = *(int *)(param_1 + 0x88);
      param_3[1] = (DAT_0065ebfc + DAT_0065ec00 + 6) * param_2;
      param_3[3] = param_3[1] + DAT_0065ebfc + DAT_0065ec00 + 6;
    }
    FUN_00491ace();
    uVar2 = 1;
  }
  else {
    if (((*(int *)(param_1 + 0x1c) == 6) &&
        (local_8 = FUN_0049ea99(param_1), *(int *)(param_1 + 0x98) <= param_2)) &&
       (iVar1 = FUN_0049eb44(local_8,param_1,2,0x18,0,0), param_2 < iVar1)) {
      local_c = FUN_0049eb44(local_8,param_1,2,0x17,0,0);
      iVar1 = FUN_0049eb44(local_8,param_1,2,0x1a,0,0);
      local_10 = FUN_0049eb44(local_8,param_1,2,0x1e,0,0);
      FUN_0049f09b(param_1,&local_24);
      param_2 = param_2 - *(int *)(param_1 + 0x98);
      param_3[1] = (param_2 / local_10) * local_c + *(int *)(param_1 + 0x10);
      *param_3 = (param_2 % local_10) * iVar1 + *(int *)(param_1 + 0xc);
      param_3[3] = param_3[1] + local_c;
      param_3[2] = iVar1 + *param_3;
      local_24 = *(undefined4 *)(param_1 + 0xc);
      local_20 = *(undefined4 *)(param_1 + 0x10);
      local_1c = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x18);
      local_18 = *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x14);
      uVar2 = FUN_00495cc4(param_3,&local_24);
      return uVar2;
    }
    param_3[2] = 0;
    *param_3 = 0;
    param_3[3] = 0;
    param_3[1] = 0;
    uVar2 = 0;
  }
  return uVar2;
}

