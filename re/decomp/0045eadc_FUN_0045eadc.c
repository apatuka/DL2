// FUN_0045eadc @ 0045eadc size=435 sig=undefined FUN_0045eadc() cc=unknown
// callers: 
// callees: DisableMainInterface_c1a4,FUN_0044d1a4,FUN_0043a914,FUN_00459068,FUN_0044d600,FUN_0046e56c,FUN_0047ee9c,FUN_0042836c,FUN_00449cc4,SyncCreateBuilding,FUN_00449dec
// strings: \"You must start a settlement before you can make buildings there.  Give a Colonizer the 'Build Settlement' mission and move it into this territory.  The next turn the territory will be yours!\"|\"Oolan's Advice\"|\"Sea Platforms must be built off a coast. You cannot build one in this territory.\"

undefined4 FUN_0045eadc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = DAT_00583d68;
  DisableMainInterface_c1a4(0);
  if ((&DAT_004f9dc5)[DAT_00583d68 * 0x32] == '\x02') {
    param_1 = param_1 + -0x32;
  }
  else if ((&DAT_004f9dc5)[DAT_00583d68 * 0x32] == '\x05') {
    param_1 = param_1 + -200;
  }
  iVar2 = FUN_00449cc4(param_1,param_2,&local_8,&local_c);
  if ((((iVar2 == 0) && (FUN_0047ee9c(local_8,local_c,&local_10,&local_14), -1 < local_10)) &&
      (local_10 < 6)) && ((-1 < local_14 && (local_14 < 6)))) {
    iVar2 = local_14 * 6 + local_10;
    if ((*(short *)(DAT_00657de0 + 0x30) == 0) &&
       ((DAT_004d5aa0 == '\0' && (iVar3 = FUN_0044d1a4(DAT_00657de0,0x11,0), iVar3 == -1)))) {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_must_start_a_settlement_befo_00509718,4,0
                   ,0xc);
      return 0;
    }
    if ((DAT_004d5aa0 != '\0') && (iVar1 == 0x26)) {
      if (*(int *)(DAT_00657de0 + 0x8ac) == 0) {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Sea_Platforms_must_be_built_off_a_0050977c,
                     4,0,0xc);
        return 0;
      }
      if ((*(char *)(DAT_00657de0 + 0x20) != DAT_0058f1f4) && (cRam004fa52f != '\v')) {
        FUN_0046e56c(DAT_00657de0,DAT_0058f1f4);
      }
      SyncCreateBuilding(DAT_00657de0,0x26);
      FUN_0043a914();
      FUN_00449dec();
      return 1;
    }
    uVar4 = FUN_0044d600(DAT_00657de0,iVar1,iVar2);
    switch(uVar4) {
    case 0:
      if (((DAT_004d5aa0 != '\0') && (*(char *)(DAT_00657de0 + 0x20) != DAT_0058f1f4)) &&
         ((&DAT_004f9dc3)[iVar1 * 0x32] != '\v')) {
        FUN_0046e56c(DAT_00657de0,DAT_0058f1f4);
      }
      FUN_00482ac4(0x83,0,1,0,0,0);
      FUN_0047597c(DAT_00657de0,iVar1,iVar2);
      if ((DAT_004d5aa0 != '\0') && ((iVar1 == 0x2b || (iVar1 == 0x2c)))) {
        FUN_0046f0e0(0);
      }
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_0043a914();
      FUN_00449dec();
      uVar4 = 1;
      break;
    case 1:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_This_building_cannot_be_set_down_0050971c,4,0
                   ,0xc);
      uVar4 = 0;
      break;
    case 2:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Buildings_cannot_be_built_on_top_00509720,4,0
                   ,0xc);
      uVar4 = 0;
      break;
    case 3:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_There_is_too_much_water_in_this_s_00509724,4,
                   0,0xc);
      uVar4 = 0;
      break;
    case 4:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_already_have_a_City_Center_i_0050972c,4,0
                   ,0xc);
      uVar4 = 0;
      break;
    case 5:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_only_build_ports_in_terr_00509728,4,0
                   ,0xc);
      uVar4 = 0;
      break;
    case 6:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_t_build_on_a_wasteland__00509750,4,0,
                   0xc);
      uVar4 = 0;
      break;
    case 7:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_One_can_not_build_that_building_o_00509764,4,
                   0,0xc);
      uVar4 = 0;
      break;
    case 8:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_already_have_a_Sea_Platform_i_00509768,4,
                   0,0xc);
      uVar4 = 0;
      break;
    case 9:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_One_can_not_build_that_building_o_0050976c,4,
                   0,0xc);
      uVar4 = 0;
      break;
    case 10:
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_already_have_a_Shrine_in_thi_00509778,4,0
                   ,0xc);
      uVar4 = 0;
      break;
    default:
      goto LAB_0045ee78;
    }
  }
  else {
LAB_0045ee78:
    FUN_00459068();
    uVar4 = 1;
  }
  return uVar4;
}

