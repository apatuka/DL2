// FUN_0043735c @ 0043735c size=611 sig=undefined FUN_0043735c() cc=unknown
// callers: FUN_00437718
// callees: FUN_0049eb44,FUN_004a60b1,FUN_004a2004,FUN_004a3de6,FUN_004a19b4,sprintf,FUN_00414f04,FUN_004493dc
// strings: \"%d %s\"

undefined4 FUN_0043735c(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined1 local_814 [1024];
  undefined1 local_414 [1024];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00558f30 = param_1;
  DAT_00558f34 = param_2;
  if (DAT_004d59b4 == 0xf) {
    uVar1 = 0;
  }
  else {
    DAT_004c4670 = FUN_004a3de6(0,0x38303944);
    if (DAT_004c4670 == 0) {
      uVar1 = 0;
    }
    else {
      FUN_004493dc(1);
      DAT_00558f2c = DAT_004d59b4;
      DAT_004d59b4 = 0xf;
      FUN_00414f04(DAT_004c4670);
      local_14 = 0;
      local_10 = 0;
      local_c = 0x280;
      local_8 = 0x1e0;
      FUN_004a60b1(&local_14,0);
      FUN_004a2004(DAT_004c4670);
      FUN_0049eb44(DAT_004c4670,8,1,7,0,&LAB_00414a6c);
      FUN_0049eb44(DAT_004c4670,9,1,7,0,&LAB_00414a6c);
      FUN_004a19b4(DAT_004c4670,2,1,0xd,(&DAT_004c4670)[param_3] + 0x3fa);
      FUN_0049eb44(DAT_004c4670,4,1,0xf,0,(&PTR_s_credits_00509098)[param_3]);
      FUN_0049eb44(DAT_004c4670,3,1,0xe,0x100,local_814);
      sprintf(local_414,local_814,DAT_00558f30);
      FUN_0049eb44(DAT_004c4670,3,1,0xf,0,local_414);
      FUN_0049eb44(DAT_004c4670,0xe,1,0xf,0,
                   (&PTR_s_ChCh_t_00509038)
                   [(char)(&DAT_0059f162)[*(char *)(param_2 + 0x20) * 0x2d8]]);
      sprintf(local_414,s__d__s_004c46ac,*(undefined4 *)(param_1 + 0x3a + param_3 * 4),
              (&PTR_s_credits_005090f0)[param_3]);
      FUN_0049eb44(DAT_004c4670,5,1,0xf,0,local_414);
      FUN_0049eb44(DAT_004c4670,0x10,1,0xe,0,&DAT_00558f38);
      sprintf(local_414,&DAT_004c46a9,0);
      FUN_0049eb44(DAT_004c4670,0x10,1,0xf,0,local_414);
      FUN_0049eb44(DAT_004c4670,0x12,1,0xf,0,local_414);
      FUN_0049eb44(DAT_004c4670,0x14,1,0xf,0,local_414);
      uVar1 = 1;
    }
  }
  return uVar1;
}

