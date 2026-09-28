// FUN_004590f0 @ 004590f0 size=317 sig=undefined FUN_004590f0() cc=unknown
// callers: FUN_0045cff4,FUN_0041e1fc,FUN_0045cd88,FUN_0045b304,FUN_00421584,FUN_0045ee88,FUN_0041a14c
// callees: FUN_0048c28d,FUN_004878a8,FUN_0048d13d,FUN_00459068,FUN_004590d4

undefined4
FUN_004590f0(undefined4 param_1,undefined4 param_2,int param_3,int param_4,uint param_5,uint param_6
            ,int param_7,undefined4 param_8)

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
  if ((param_5 == 0) || (param_6 == 0)) {
    uVar3 = 0;
  }
  else {
    if (((DAT_00583d30 == 0) || (*(int *)(DAT_00583d30 + 4) < (int)param_5)) ||
       (*(int *)(DAT_00583d30 + 8) < (int)param_6)) {
      if (DAT_00583d30 != 0) {
        FUN_0048d13d(DAT_00583d30);
      }
      uVar4 = param_6;
      if ((int)param_6 < 0x10) {
        uVar4 = 0x10;
      }
      uVar2 = param_5;
      if ((int)param_5 < 0x10) {
        uVar2 = 0x10;
      }
      DAT_00583d30 = FUN_0048c28d(uVar2,uVar4,0);
      if (DAT_00583d30 == 0) {
        return 0;
      }
    }
    DAT_00583d38 = param_2;
    DAT_00583d58 = 0;
    DAT_00583d44 = param_5;
    DAT_00583d48 = param_6;
    DAT_00583d50 = param_1;
    DAT_00583d34 = 0;
    DAT_00583d54 = param_8;
    DAT_00583d4c = param_7;
    iVar1 = (int)param_5 >> 1;
    if (iVar1 < 0) {
      iVar1 = iVar1 + (uint)((param_5 & 1) != 0);
    }
    DAT_00583d3c = param_3 - iVar1;
    if (param_7 == 0) {
      iVar1 = (int)param_6 >> 1;
      if (iVar1 < 0) {
        iVar1 = iVar1 + (uint)((param_6 & 1) != 0);
      }
      DAT_00583d40 = param_4 - iVar1;
    }
    else if (param_7 == 1) {
      DAT_00583d40 = param_4 - (param_6 - 0x19);
    }
    else if (param_7 == 2) {
      DAT_00583d40 = param_4 - (param_6 - 0x32);
    }
    DAT_00583d2c = 0;
    uVar3 = 1;
  }
  return uVar3;
}

