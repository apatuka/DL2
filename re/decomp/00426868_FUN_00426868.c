// FUN_00426868 @ 00426868 size=537 sig=undefined FUN_00426868() cc=unknown
// callers: FUN_00426ba4
// callees: FUN_0048de13,FUN_0045839c,FUN_0042662c,FUN_004a3de6,FUN_00458138,FUN_004581a8,FUN_0048de03,FUN_00458298,FUN_004a2004,FUN_004493dc,FUN_0042836c,FUN_00414f04,FUN_004a60b1
// strings: \"The TCP/IP (Internet) service is not available.  Please exit the game and make sure that you have TCP/IP installed and that it is configured correctly.\"|\"Network Error\"|\"The IPX (LAN) service is not available.  Please exit the game and make sure that you have IPX installed and that it is configured correctly.\"|\"The Modem Play service is not available.  Please exit the game and use the Modem's control panel to make sure that your modem is properly installed.\"|\"The Serial Connection service is not available.  Please exit the game and make sure that your COM ports are installed and correctly configured.\"|\"The TCP/IP (Internet) service could not be initialized.  Please exit the game and make sure that your TCP/IP settings are correct.\"|\"The IPX (LAN) service could not be initialized.  Please exit the game and make sure that your IPX networking is properly configured.\"|\"The Modem Play service could not be initialized.  Please exit the game and make sure that your modem is connected, turned on, and  properly configured.\"|\"The Serial Connection service could not be initialized.  Please exit the game and make sure that your serial ports are correctly configured.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00426868(void)

{
  uint uVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004b7d20 = FUN_004a3de6(0,0x30333044);
  if (DAT_004b7d20 == 0) {
    return 0;
  }
  FUN_004493dc(1);
  DAT_00557568 = DAT_004d59b4;
  DAT_004d59b4 = 0x3f;
  FUN_00414f04(DAT_004b7d20);
  local_14 = DAT_004b7d28;
  local_10 = DAT_004b7d24;
  local_c = DAT_004b7d30;
  local_8 = DAT_004b7d2c;
  FUN_004a60b1(&local_14,0);
  FUN_004a2004(DAT_004b7d20);
  uVar1 = FUN_00458138();
  if ((uVar1 & DAT_004d5a50) != 0) {
    iVar2 = FUN_004581a8(0,DAT_004d5a50);
    if (iVar2 != 0) {
      FUN_0045839c();
      DAT_004d5130 = 0xffffffff;
      DAT_00557574 = 0;
      FUN_0042662c();
      _DAT_0055756c = FUN_0048de13();
      _DAT_0055756c = _DAT_0055756c / 0x3c;
      DAT_00557570 = FUN_0048de03();
      if (DAT_004d5a50 == 4) {
        DAT_00557574 = 1;
      }
      return 1;
    }
    if (DAT_004d5a50 == 1) {
      FUN_00458298();
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_Modem_Play_service_is_not_av_005092d4,4,0,
                   3);
      return 0;
    }
    if (DAT_004d5a50 != 2) {
      if (DAT_004d5a50 == 4) {
        FUN_00458298();
        FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_IPX__LAN__service_is_not_ava_005092d0,4,
                     0,3);
        return 0;
      }
      if (DAT_004d5a50 == 8) {
        FUN_00458298();
        FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_TCP_IP__Internet__service_is_005092cc,4,
                     0,3);
        return 0;
      }
    }
    FUN_00458298();
    FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_Serial_Connection_service_is_005092d8,4,0,3)
    ;
    return 0;
  }
  if (DAT_004d5a50 == 1) {
    FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_Modem_Play_service_could_not_005092e4,4,0,3)
    ;
    return 0;
  }
  if (DAT_004d5a50 != 2) {
    if (DAT_004d5a50 == 4) {
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_IPX__LAN__service_could_not_b_005092e0,4,0
                   ,3);
      return 0;
    }
    if (DAT_004d5a50 == 8) {
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_TCP_IP__Internet__service_co_005092dc,4,0,
                   3);
      return 0;
    }
  }
  FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_Serial_Connection_service_co_005092e8,4,0,3);
  return 0;
}

