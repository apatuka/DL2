// FUN_0043a394 @ 0043a394 size=275 sig=undefined FUN_0043a394() cc=unknown
// callers: FUN_0043a568
// callees: FUN_0049eb44,FUN_004a60b1,FUN_004a2004,FUN_004a3de6,FUN_004a19b4,sprintf,FUN_00414f04,FUN_004493dc
// strings: \"%s\\n\\n%s\\n\\n%s\"

undefined4 FUN_0043a394(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_004d59b4 == 4) {
    uVar1 = 0;
  }
  else {
    sprintf(&DAT_005598e8,&DAT_004c485c,param_1);
    sprintf(&DAT_005599b0,s__s__s__s_004c485f,param_1,param_2,param_3);
    DAT_004c4858 = FUN_004a3de6(0,0x36303944);
    if (DAT_004c4858 == 0) {
      uVar1 = 0;
    }
    else {
      FUN_004493dc(1);
      DAT_005598e4 = DAT_004d59b4;
      DAT_004d59b4 = 4;
      FUN_00414f04(DAT_004c4858);
      local_14 = 0;
      local_10 = 0;
      local_c = 0x280;
      local_8 = 0x1e0;
      FUN_004a60b1(&local_14,0);
      FUN_004a2004(DAT_004c4858);
      FUN_004a19b4(DAT_004c4858,4,1,0xd,param_4 + 1000);
      FUN_0049eb44(DAT_004c4858,2,1,0xf,0,&DAT_005598e8);
      FUN_0049eb44(DAT_004c4858,3,1,0xf,0,&DAT_005599b0);
      uVar1 = 1;
    }
  }
  return uVar1;
}

