// FUN_00428b74 @ 00428b74 size=2286 sig=undefined FUN_00428b74() cc=unknown
// callers: FUN_0042a36c
// callees: FUN_0042a2c4,FUN_004412d4,sprintf,FUN_0044a000,FUN_0042a318,FUN_004418ac,FUN_0049eb44
// strings: \"Non-aggression\"|\"Have %s pact with the %s\"|\"Military\"|\"Backstabbed %s pact with the %s\"|\"No %s pact with the %s\"|\"Victory\"|\"Technology\"|\"Intelligence\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00428b74(int param_1)

{
  int iVar1;
  undefined1 local_414 [1024];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_1 <= DAT_004d5aec + -2) {
    FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9c44 + param_1 * 4),1,0xb,1,0);
    local_14 = 10000;
    local_10 = 10000;
    local_c = 10000;
    local_8 = 10000;
    FUN_0049eb44(DAT_004b9bf0,0x2e,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x2f,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x30,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x31,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x32,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x33,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x34,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x35,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x36,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x37,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x38,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x39,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3a,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3b,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3c,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3d,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3e,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x3f,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x40,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x41,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x45,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x42,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x44,1,0xd,0,&local_14);
    FUN_0049eb44(DAT_004b9bf0,0x43,1,0xd,0,&local_14);
    local_10 = DAT_004b9c04;
    local_14 = DAT_004b9c08;
    local_8 = DAT_004b9c0c;
    local_c = DAT_004b9c10;
    iVar1 = FUN_004412d4(DAT_0058f1f4,(&DAT_00557bb4)[param_1],1);
    if (iVar1 == 0) {
      iVar1 = FUN_004412d4(DAT_0058f1f4,(&DAT_00557bb4)[param_1],2);
      if (iVar1 == 0) {
        iVar1 = FUN_004418ac(DAT_0058f1f4,(&DAT_00557bb4)[param_1],2);
        if (iVar1 == 0) {
          FUN_0049eb44(DAT_004b9bf0,0x34,1,0xd,0,&local_14);
          _DAT_00557be4 = 0x34;
          sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Military_00508fc0,
                  (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]])
          ;
        }
        else {
          FUN_0049eb44(DAT_004b9bf0,0x44,1,0xd,0,&local_14);
          _DAT_00557be4 = 0x44;
          sprintf(local_414,PTR_s_Backstabbed__s_pact_with_the__s_005093d0,PTR_s_Military_00508fc0,
                  (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]])
          ;
        }
      }
      else {
        FUN_0049eb44(DAT_004b9bf0,0x39,1,0xd,0,&local_14);
        _DAT_00557be4 = 0x39;
        sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Military_00508fc0,
                (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
      }
    }
    else {
      FUN_0049eb44(DAT_004b9bf0,0x38,1,0xd,0,&local_14);
      _DAT_00557be4 = 0x38;
      sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Non_aggression_00508fbc,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    FUN_0049eb44(DAT_004b9bf0,4,1,0xf,0,local_414);
    local_10 = DAT_004b9c14;
    local_14 = DAT_004b9c18;
    local_8 = DAT_004b9c1c;
    local_c = DAT_004b9c20;
    iVar1 = FUN_004412d4(DAT_0058f1f4,(&DAT_00557bb4)[param_1],0x10);
    if (iVar1 == 0) {
      iVar1 = FUN_004418ac(DAT_0058f1f4,(&DAT_00557bb4)[param_1],0x10);
      if (iVar1 == 0) {
        FUN_0049eb44(DAT_004b9bf0,0x35,1,0xd,0,&local_14);
        DAT_00557be8 = 0x35;
        sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Victory_00508ff8,
                (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
      }
      else {
        FUN_0049eb44(DAT_004b9bf0,0x43,1,0xd,0,&local_14);
        DAT_00557be8 = 0x43;
        sprintf(local_414,PTR_s_Backstabbed__s_pact_with_the__s_005093d0,PTR_s_Victory_00508ff8,
                (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
      }
    }
    else {
      FUN_0049eb44(DAT_004b9bf0,0x3a,1,0xd,0,&local_14);
      DAT_00557be8 = 0x3a;
      sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Victory_00508ff8,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    FUN_0049eb44(DAT_004b9bf0,5,1,0xf,0,local_414);
    local_10 = DAT_004b9c24;
    local_14 = DAT_004b9c28;
    local_8 = DAT_004b9c2c;
    local_c = DAT_004b9c30;
    iVar1 = FUN_004412d4(DAT_0058f1f4,(&DAT_00557bb4)[param_1],8);
    if (iVar1 == 0) {
      FUN_0049eb44(DAT_004b9bf0,0x36,1,0xd,0,&local_14);
      DAT_00557bec = 0x36;
      sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Technology_00508fd8,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    else {
      FUN_0049eb44(DAT_004b9bf0,0x3b,1,0xd,0,&local_14);
      DAT_00557bec = 0x3b;
      sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Technology_00508fd8,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    FUN_0049eb44(DAT_004b9bf0,6,1,0xf,0,local_414);
    local_10 = DAT_004b9c34;
    local_14 = DAT_004b9c38;
    local_8 = DAT_004b9c3c;
    local_c = DAT_004b9c40;
    iVar1 = FUN_004412d4(DAT_0058f1f4,(&DAT_00557bb4)[param_1],4);
    if (iVar1 == 0) {
      FUN_0049eb44(DAT_004b9bf0,0x37,1,0xd,0,&local_14);
      DAT_00557bf0 = 0x37;
      sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Intelligence_00508fc8,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    else {
      FUN_0049eb44(DAT_004b9bf0,0x3c,1,0xd,0,&local_14);
      DAT_00557bf0 = 0x3c;
      sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Intelligence_00508fc8,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    }
    FUN_0049eb44(DAT_004b9bf0,7,1,0xf,0,local_414);
    DAT_00557be0 = param_1;
    FUN_0049eb44(DAT_004b9bf0,3,1,0xf,0,
                 (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(&DAT_00557bb4)[param_1] * 0x2d8]]);
    FUN_0042a318();
    FUN_0042a2c4();
    FUN_0044a000();
  }
  return;
}

