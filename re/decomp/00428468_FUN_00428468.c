// FUN_00428468 @ 00428468 size=438 sig=undefined FUN_00428468() cc=unknown
// callers: FUN_00428824
// callees: sprintf,FUN_004493dc,FUN_00414f04,FUN_004a2004,FUN_004a3de6,FUN_0049eb44,FUN_004a60b1
// strings: \"Move Resources\"|\"How many units of this resource do you wish to transfer?\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00428468(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 local_10 [12];
  
  DAT_004b7dcc = FUN_004a3de6(0,0x39323044);
  if (DAT_004b7dcc == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_00557b9c = DAT_004d59b4;
    DAT_004d59b4 = 0x51;
    FUN_00414f04(DAT_004b7dcc);
    local_20 = DAT_004b7dd4;
    local_1c = DAT_004b7dd0;
    local_18 = DAT_004b7ddc;
    local_14 = DAT_004b7dd8;
    FUN_004a60b1(&local_20,0);
    FUN_004a2004(DAT_004b7dcc);
    FUN_0049eb44(DAT_004b7dcc,7,1,7,0,&LAB_00414a6c);
    sprintf(local_10,&DAT_004b7de0,param_2);
    FUN_0049eb44(DAT_004b7dcc,4,1,0xf,0,local_10);
    FUN_0049eb44(DAT_004b7dcc,7,1,0xf,0,&DAT_004b7de3);
    FUN_0049eb44(DAT_004b7dcc,7,1,0x1c,4,0);
    FUN_0049eb44(DAT_004b7dcc,7,1,0x34,1,0);
    sprintf(local_10,&DAT_004b7de0,param_3);
    FUN_0049eb44(DAT_004b7dcc,0xb,1,0xf,0,local_10);
    if (param_1 < 0xb) {
      FUN_0049eb44(DAT_004b7dcc,2,1,0xf,0,PTR_s_Move_Resources_00509dbc);
      FUN_0049eb44(DAT_004b7dcc,5,1,0xf,0,(&PTR_s_credits_005090f0)[param_1]);
      FUN_0049eb44(DAT_004b7dcc,6,1,0xf,0,PTR_s_How_many_units_of_this_resource_d_00509dc8);
    }
    uVar1 = 1;
    DAT_00557ba0 = 0;
    _DAT_00557ba4 = param_1;
    DAT_00557ba8 = param_3;
  }
  return uVar1;
}

