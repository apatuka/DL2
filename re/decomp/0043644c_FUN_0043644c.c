// FUN_0043644c @ 0043644c size=1001 sig=undefined FUN_0043644c() cc=unknown
// callers: FUN_0043694c
// callees: FUN_0049eb44,FUN_004a2004,FUN_004a3de6,FUN_00436424,FUN_00414f04,FUN_004493dc

undefined4 FUN_0043644c(int param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004c4660 = FUN_004a3de6(0,0x38303044);
  if (DAT_004c4660 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00558eb0 = DAT_004d59b4;
    DAT_004d59b4 = 0x29;
    FUN_00414f04(DAT_004c4660);
    FUN_004a2004(DAT_004c4660);
    local_10 = 10000;
    local_14 = 10000;
    local_c = 0x27d8;
    local_8 = 0x2738;
    FUN_0049eb44(DAT_004c4660,2,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,3,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,4,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,5,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,6,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,7,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,8,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,9,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,10,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0xb,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0xc,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0xd,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0xe,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0xf,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004c4660,0x10,1,0xd,0,&local_14);
    if (param_1 == 0x2c) {
      local_14 = 0x3b;
      local_10 = 0x151;
      local_c = 0xbf;
      local_8 = 0x16e;
      FUN_0049eb44(DAT_004c4660,5,1,0xd,0,&local_14);
      local_14 = 0xca;
      local_10 = 0x151;
      local_c = 0x14e;
      local_8 = 0x16e;
      FUN_0049eb44(DAT_004c4660,8,1,0xd,0,&local_14);
      local_14 = 0x156;
      local_10 = 0x151;
      local_c = 0x1da;
      local_8 = 0x16e;
      FUN_0049eb44(DAT_004c4660,6,1,0xd,0,&local_14);
    }
    else if (param_1 == 0x2e) {
      local_10 = 3;
      local_14 = 0x98;
      local_8 = 0x20;
      local_c = 0x11c;
      FUN_0049eb44(DAT_004c4660,0xb,1,0xd,0,&local_14);
      local_10 = 0x24;
      local_14 = 0x98;
      local_8 = 0x41;
      local_c = 0x11c;
      FUN_0049eb44(DAT_004c4660,0xc,1,0xd,0,&local_14);
    }
    else if (param_1 == 0x2f) {
      local_14 = 0xca;
      local_10 = 0x151;
      local_c = 0x14e;
      local_8 = 0x16e;
      FUN_0049eb44(DAT_004c4660,0xd,1,0xd,0,&local_14);
      local_14 = 0xca;
      local_10 = 0x171;
      local_c = 0x14e;
      local_8 = 0x18e;
      FUN_0049eb44(DAT_004c4660,0xe,1,0xd,0,&local_14);
    }
    else if (param_1 == 0x31) {
      local_14 = 0xca;
      local_10 = 0x151;
      local_c = 0x14e;
      local_8 = 0x16e;
      FUN_0049eb44(DAT_004c4660,6,1,0xd,0,&local_14);
      local_14 = 0xca;
      local_10 = 0x171;
      local_c = 0x14e;
      local_8 = 0x18e;
      FUN_0049eb44(DAT_004c4660,8,1,0xd,0,&local_14);
    }
    FUN_00436424();
    uVar1 = 1;
  }
  return uVar1;
}

