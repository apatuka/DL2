// FUN_00459230 @ 00459230 size=371 sig=undefined FUN_00459230() cc=unknown
// callers: FUN_0045cff4,FUN_0045cd88
// callees: FUN_0048c28d,FUN_00490ab3,FUN_004878a8,FUN_0048d13d,FUN_00459068,FUN_004590d4

undefined4
FUN_00459230(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            ,int param_6,uint param_7,uint param_8,int param_9,undefined4 param_10)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  
  FUN_004878a8();
  iVar1 = FUN_004590d4();
  if (iVar1 != 0) {
    FUN_00459068();
  }
  if ((param_7 == 0) || (param_8 == 0)) {
    uVar3 = 0;
  }
  else {
    if (((DAT_00583d30 == 0) || (*(int *)(DAT_00583d30 + 4) < (int)param_7)) ||
       (*(int *)(DAT_00583d30 + 8) < (int)param_8)) {
      if (DAT_00583d30 != 0) {
        FUN_0048d13d(DAT_00583d30);
      }
      uVar4 = param_8;
      if ((int)param_8 < 0x10) {
        uVar4 = 0x10;
      }
      uVar2 = param_7;
      if ((int)param_7 < 0x10) {
        uVar2 = 0x10;
      }
      DAT_00583d30 = FUN_0048c28d(uVar2,uVar4,0);
      if (DAT_00583d30 == 0) {
        return 0;
      }
    }
    DAT_00583d58 = FUN_00490ab3(0,0x47414d49,param_2,0,0x80000000);
    if (DAT_00583d58 == 0) {
      uVar3 = 0;
    }
    else {
      DAT_00583d38 = 0;
      DAT_00583d44 = param_7;
      DAT_00583d48 = param_8;
      DAT_00583d50 = param_1;
      DAT_00583d34 = 0;
      DAT_00583d54 = param_10;
      DAT_00583d4c = param_9;
      DAT_00583d5c = param_3;
      iVar1 = (int)param_7 >> 1;
      DAT_00583d60 = param_4;
      if (iVar1 < 0) {
        iVar1 = iVar1 + (uint)((param_7 & 1) != 0);
      }
      DAT_00583d3c = param_5 - iVar1;
      if (param_9 == 0) {
        iVar1 = (int)param_8 >> 1;
        if (iVar1 < 0) {
          iVar1 = iVar1 + (uint)((param_8 & 1) != 0);
        }
        DAT_00583d40 = param_6 - iVar1;
      }
      else if (param_9 == 1) {
        DAT_00583d40 = param_6 - (param_8 - 0x19);
      }
      else if (param_9 == 2) {
        DAT_00583d40 = param_6 - (param_8 - 0x32);
      }
      uVar3 = 1;
      DAT_00583d2c = 0;
    }
  }
  return uVar3;
}

