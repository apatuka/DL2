// FUN_0042d0ac @ 0042d0ac size=461 sig=undefined FUN_0042d0ac() cc=unknown
// callers: FUN_0042d3dc
// callees: FUN_0042c794,FUN_004493dc,FUN_004503f4,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1

undefined4 FUN_0042d0ac(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004bf8fc = FUN_004a3de6(0,0x39313044);
  if (DAT_004bf8fc == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557c14 = DAT_004d59b4;
    DAT_004d59b4 = 0x4d;
    FUN_00414f04(DAT_004bf8fc);
    local_14 = DAT_004bf904;
    local_10 = DAT_004bf900;
    local_c = DAT_004bf90c;
    local_8 = DAT_004bf908;
    FUN_004a60b1(&local_14,0);
    FUN_004a2004(DAT_004bf8fc);
    FUN_0049eb44(DAT_004bf8fc,1,1,7,0,FUN_0042cfbc);
    FUN_0042c794();
    local_14 = 0x13d;
    local_10 = 0x148;
    local_c = 0x155;
    local_8 = 0x160;
    if ((param_1 & 1) == 0) {
      if ((param_1 & 2) != 0) {
        FUN_0049eb44(DAT_004bf8fc,0x30,1,0xd,0,&local_14);
      }
    }
    else {
      FUN_0049eb44(DAT_004bf8fc,0x2f,1,0xd,0,&local_14);
    }
    if ((param_1 & 0x10) != 0) {
      local_14 = 0x15c;
      local_10 = 0x148;
      local_c = 0x174;
      local_8 = 0x160;
      FUN_0049eb44(DAT_004bf8fc,0x31,1,0xd,0,&local_14);
    }
    if ((param_1 & 8) != 0) {
      local_14 = 0x13d;
      local_10 = 0x167;
      local_c = 0x155;
      local_8 = 0x17f;
      FUN_0049eb44(DAT_004bf8fc,0x32,1,0xd,0,&local_14);
    }
    if ((param_1 & 4) != 0) {
      local_14 = 0x15c;
      local_10 = 0x167;
      local_c = 0x174;
      local_8 = 0x17f;
      FUN_0049eb44(DAT_004bf8fc,0x33,1,0xd,0,&local_14);
    }
    DAT_00557c50 = FUN_004503f4(param_2,0xf,0xffffffff);
    DAT_004bf910 = 0;
    uVar1 = 1;
  }
  return uVar1;
}

