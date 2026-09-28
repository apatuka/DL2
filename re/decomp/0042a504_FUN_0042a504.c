// FUN_0042a504 @ 0042a504 size=197 sig=undefined FUN_0042a504() cc=unknown
// callers: 
// callees: FUN_0049eb44

void FUN_0042a504(int param_1,undefined4 param_2,int param_3)

{
  undefined1 local_414 [1024];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = 10000;
  local_10 = 10000;
  local_c = 10000;
  local_8 = 10000;
  FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_00557be4 + param_1 * 4),1,0xd,0,&local_14);
  local_10 = *(undefined4 *)(&DAT_004b9e9c + param_1 * 4);
  local_14 = *(undefined4 *)(&DAT_004b9eac + param_1 * 4);
  local_8 = *(undefined4 *)(&DAT_004b9ebc + param_1 * 4);
  local_c = *(undefined4 *)(&DAT_004b9ecc + param_1 * 4);
  FUN_0049eb44(DAT_004b9bf0,param_2,1,0xd,0,&local_14);
  *(undefined4 *)(&DAT_00557be4 + param_1 * 4) = param_2;
  switch(param_2) {
  case 0x2e:
    sprintf(local_414,PTR_s_Propose__s_pact_to_the__s_005093c0,PTR_s_Non_aggression_00508fbc,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x2f:
    sprintf(local_414,PTR_s_Propose__s_pact_to_the__s_005093c0,PTR_s_Military_00508fc0,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x30:
    sprintf(local_414,PTR_s_Propose__s_pact_to_the__s_005093c0,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x31:
    sprintf(local_414,PTR_s_Propose__s_pact_to_the__s_005093c0,PTR_s_Technology_00508fd8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x32:
    sprintf(local_414,PTR_s_Propose__s_pact_to_the__s_005093c0,PTR_s_Intelligence_00508fc8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x33:
  case 0x34:
    sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,
            PTR_s_Military_or_Non_aggression_005093d8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x35:
    sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x36:
    sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Technology_00508fd8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x37:
    sprintf(local_414,PTR_s_No__s_pact_with_the__s_005093d4,PTR_s_Intelligence_00508fc8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x38:
    sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Non_aggression_00508fbc,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x39:
    sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Military_00508fc0,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3a:
    sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3b:
    sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Technology_00508fd8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3c:
    sprintf(local_414,PTR_s_Have__s_pact_with_the__s_005093c4,PTR_s_Intelligence_00508fc8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3d:
    sprintf(local_414,PTR_s_Break__s_pact_with_the__s_005093c8,PTR_s_Non_aggression_00508fbc,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3e:
    sprintf(local_414,PTR_s_Break__s_pact_with_the__s_005093c8,PTR_s_Military_00508fc0,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x3f:
    sprintf(local_414,PTR_s_Break__s_pact_with_the__s_005093c8,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x40:
    sprintf(local_414,PTR_s_Break__s_pact_with_the__s_005093c8,PTR_s_Technology_00508fd8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x41:
    sprintf(local_414,PTR_s_Break__s_pact_with_the__s_005093c8,PTR_s_Intelligence_00508fc8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x42:
    sprintf(local_414,PTR_s_Backstab__s_pact_with_the__s_005093cc,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x43:
    sprintf(local_414,PTR_s_Backstabbed__s_pact_with_the__s_005093d0,PTR_s_Victory_00508ff8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x44:
    sprintf(local_414,PTR_s_Backstabbed__s_pact_with_the__s_005093d0,
            PTR_s_Military_or_Non_aggression_005093d8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
    break;
  case 0x45:
    sprintf(local_414,PTR_s_Backstab__s_pact_with_the__s_005093cc,
            PTR_s_Military_or_Non_aggression_005093d8,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_3 * 0x2d8]]);
  }
  FUN_0049eb44(DAT_004b9bf0,*(undefined4 *)(&DAT_004b9edc + param_1 * 4),1,0xf,0,local_414);
  return;
}

