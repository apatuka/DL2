// FUN_00425f58 @ 00425f58 size=486 sig=undefined FUN_00425f58() cc=unknown
// callers: FUN_00426594
// callees: FUN_004a4025,FUN_004258f8,FUN_004a3de6,FUN_0048c85e,FUN_004a2004,FUN_004256f4,FUN_0048c28d,FUN_004493dc,FUN_004257f0,FUN_00425ac4,FUN_00414f04,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_00425f58(int param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b7ce4 = FUN_004a3de6(0,0x36323044);
  if (DAT_004b7ce4 == 0) {
    uVar1 = 0;
  }
  else {
    if ((DAT_004b7d04 == 0) &&
       (DAT_004b7d04 = FUN_0048c28d(DAT_0058f1c0,DAT_0058f1c4,DAT_004d5a8c), DAT_004b7d04 == 0)) {
      FUN_004a4025(DAT_004b7ce4);
      DAT_004b7ce4 = 0;
      return 0;
    }
    local_14 = 0;
    local_10 = 0;
    local_8 = 0x1e0;
    local_c = 0x280;
    FUN_0048c85e(DAT_004d5c28,DAT_004b7d04,&local_14,&local_14,&local_14,&local_14,0);
    FUN_004493dc(1);
    DAT_00557550 = DAT_004d59b4;
    DAT_004d59b4 = 0x12;
    FUN_00414f04(DAT_004b7ce4);
    local_14 = DAT_004b7cec;
    local_10 = DAT_004b7ce8;
    local_c = DAT_004b7cf4;
    local_8 = DAT_004b7cf0;
    FUN_004a60b1(&local_14,0);
    DAT_004b7d0c = 0;
    FUN_004a2004(DAT_004b7ce4);
    local_14 = 10000;
    local_10 = 10000;
    local_c = 0x28a0;
    local_8 = 0x28a0;
    FUN_0049eb44(DAT_004b7ce4,10,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7ce4,0xb,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b7ce4,1,1,7,0,FUN_00425d68);
    FUN_0049eb44(DAT_004b7ce4,0xd,1,7,0,FUN_00425bc4);
    if (*(int *)(param_1 + 0x1a) == 0) {
      FUN_004258f8(param_1,0);
      FUN_004257f0(param_1);
      FUN_004256f4(param_1);
      FUN_00425ac4(param_1);
      DAT_00557554 = *(int *)(param_1 + 0x16);
    }
    else {
      DAT_00557554 = param_1;
      FUN_004256f4(param_1);
      FUN_004257f0(param_1);
      FUN_004258f8(*(undefined4 *)(param_1 + 0x1a),param_1);
      FUN_00425ac4(param_1);
    }
    uVar1 = 1;
  }
  return uVar1;
}

