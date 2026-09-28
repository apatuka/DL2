// FUN_00487e34 @ 00487e34 size=573 sig=undefined FUN_00487e34() cc=unknown
// callers: FUN_00488074,FUN_004880e0
// callees: FUN_00487980,FUN_0048463c,FUN_0048c85e,FUN_0048d2e7,FUN_00484818,FUN_004877c8,FUN_004878a8,FUN_00490ab3,FUN_0048d32c,FUN_00487820,FUN_00487df4

undefined4
FUN_00487e34(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined4 param_7)

{
  uint *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int local_24 [3];
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((DAT_004d63d4 == 0) && (iVar2 = FUN_00487980(), iVar2 == 0)) {
    DAT_0065e548 = param_4;
    FUN_004878a8();
    DAT_005126dc = FUN_00490ab3(0,0x54434950,param_1,0,0x80000000);
    if (DAT_005126dc == 0) {
      uVar3 = 0;
    }
    else {
      FUN_004877c8(DAT_004d5c28,0);
      local_24[1] = 0;
      local_24[0] = 0;
      local_24[2] = *(int *)(DAT_004d5c28 + 4);
      local_18 = *(int *)(DAT_004d5c28 + 8);
      if (((DAT_005126dc == 0) || ((*(byte *)(DAT_005126dc + 0x28) & 1) == 0)) ||
         ((*(byte *)(DAT_005126dc + 0xb4) & 1) == 0)) {
        if (param_2 == 0) {
          uVar4 = *(int *)(DAT_004d5c28 + 4) - *(int *)(DAT_005126dc + 4);
          local_14 = (int)uVar4 >> 1;
          if (local_14 < 0) {
            local_14 = local_14 + (uint)((uVar4 & 1) != 0);
          }
          uVar4 = *(int *)(DAT_004d5c28 + 8) - *(int *)(DAT_005126dc + 8);
          local_10 = (int)uVar4 >> 1;
          if (local_10 < 0) {
            local_10 = local_10 + (uint)((uVar4 & 1) != 0);
          }
        }
        else {
          param_3 = 0;
          local_14 = 0;
          local_10 = 0;
        }
        local_24[2] = *(int *)(DAT_005126dc + 4);
        local_c = local_24[2] + local_14;
        local_18 = *(int *)(DAT_005126dc + 8);
        local_8 = local_18 + local_10;
        local_24[0] = 0;
        local_24[1] = 0;
        FUN_0048c85e(DAT_005126dc,DAT_004d5c28,local_24,&local_14,0,0,0);
        if (param_5 != 0) {
          FUN_0048d2e7(DAT_004d5c28);
          FUN_0048463c(0);
          FUN_00484818(0,(local_18 + -0x18) - DAT_00508f98,local_24[2] - local_24[0],DAT_00508f98,
                       param_5,0xff);
          FUN_0048d32c();
        }
        FUN_00487df4(1);
      }
      else {
        if (DAT_004d59a0 != 0) {
          FUN_0048c85e(DAT_004d5c28,&DAT_0065e644,local_24,local_24,0,&DAT_0065e580,0);
        }
        (**(code **)(*(int *)(DAT_005126dc + 0xb8) + 0x70))(*(int *)(DAT_005126dc + 0xb8),param_7);
        puVar1 = (uint *)(*(int *)(DAT_005126dc + 0xb8) + 0x14);
        *puVar1 = *puVar1 | 2;
        if (param_2 == 0) {
          uVar4 = *(int *)(DAT_004d5c28 + 4) - *(int *)(*(int *)(DAT_005126dc + 0xb8) + 0x10);
          iVar2 = (int)uVar4 >> 1;
          if (iVar2 < 0) {
            iVar2 = iVar2 + (uint)((uVar4 & 1) != 0);
          }
          uVar4 = *(int *)(DAT_004d5c28 + 8) - *(int *)(*(int *)(DAT_005126dc + 0xb8) + 0xc);
          iVar5 = (int)uVar4 >> 1;
          if (iVar5 < 0) {
            iVar5 = iVar5 + (uint)((uVar4 & 1) != 0);
          }
        }
        else {
          iVar2 = 0;
          param_3 = 0;
          iVar5 = 0;
        }
        (**(code **)(*(int *)(DAT_005126dc + 0xb8) + 0x60))
                  (*(int *)(DAT_005126dc + 0xb8),iVar2,iVar5,0xffffffff,0xffffffff);
      }
      uVar3 = FUN_00487820(param_3,param_5,param_6);
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

