// FUN_00482964 @ 00482964 size=182 sig=undefined FUN_00482964() cc=unknown
// callers: FUN_00482a8c,InitCYGame
// callees: FUN_00482940,FUN_00496284

undefined4 FUN_00482964(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_18;
  undefined2 local_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  
  uVar2 = 0;
  local_18 = 1;
  local_16 = 2;
  local_14 = 0x5622;
  local_10 = 0x15888;
  local_c = 4;
  local_a = 0x10;
  local_8 = 0;
  if (param_1 == 0) {
    DAT_00657e20 = 0;
  }
  iVar1 = FUN_00496284(1,&local_18);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    DAT_00657e24 = 0;
    DAT_00657e28 = 0;
    DAT_00657e2c = 0;
    DAT_00657e30 = 0xffffffff;
    DAT_00657e34 = 0;
    DAT_00657e3c = 0;
    DAT_00657e38 = 0xffffffff;
  }
  DAT_00657e20 = (uint)(iVar1 != 0);
  FUN_00482940(DAT_00657e20);
  return uVar2;
}

