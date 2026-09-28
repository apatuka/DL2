// FUN_00468a28 @ 00468a28 size=619 sig=undefined FUN_00468a28() cc=unknown
// callers: 
// callees: SendSlaveInfo,FUN_004581a8,FUN_00427e5c,FUN_00427ee8,FUN_00427f04,FUN_0048d32c,FUN_00494def,FUN_00415274,FUN_0049a93f,FUN_0049a9e7,FUN_004152c0,InvalidateRect,FUN_004582e0,FUN_00427e80,FUN_0049a8ed,UpdateWindow,FUN_00436070,FUN_00493784,FUN_0042836c,FUN_00468898,FUN_00436064,FUN_00458138,FUN_0048d2e7,FUN_0048e0f7,FUN_00458298
// strings: \"Deadlock 2 is now registering with the network.\\n\\nThis can take up to 10 seconds, so you have some time to just sit and admire your monitor.\"|\"Initializing Network\"|\"Couldn't initialize connection.\"|\"Serial Error\"|\"Netbios Error\"|\"Confirm Quitting Deadlock 2\"|\"Game 1\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00468a28(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  RECT local_10;
  
  FUN_00458298();
  uVar1 = FUN_00458138();
  if ((uVar1 & DAT_004d5a50) == 0) {
    if (DAT_004d5a50 == 2) {
      FUN_0042836c(PTR_s_Serial_Error_00509c74,PTR_s_Couldn_t_initialize_connection__00509c78,4,0,3)
      ;
    }
    else {
      FUN_0042836c(PTR_s_Netbios_Error_00509c7c,PTR_s_Confirm_Quitting_Deadlock_2_00509c80,4,0,3);
    }
    if (DAT_004d59a8 == '\0') {
      DAT_004d513c = 0;
      DAT_0058ed2e = 0;
      uVar3 = 0x35;
    }
    else {
      DAT_004d59a8 = '\0';
      uVar3 = 0x35;
    }
  }
  else {
    FUN_00427e80(0,PTR_s_Initializing_Network_0050934c,
                 PTR_s_Deadlock_2_is_now_registering_wi_00509350,0,2);
    FUN_00427f04();
    iVar2 = FUN_004581a8(DAT_0058f1dc,DAT_004d5a50);
    if (iVar2 == 0) {
      if (DAT_004d5a50 == 2) {
        FUN_0042836c(PTR_s_Serial_Error_00509c74,PTR_s_Couldn_t_initialize_connection__00509c78,4,0,
                     3);
      }
      else {
        FUN_0042836c(PTR_s_Netbios_Error_00509c7c,PTR_s_Couldn_t_initialize_connection__00509c78,4,0
                     ,3);
      }
      FUN_00427ee8();
      if (DAT_004d59a8 == '\0') {
        DAT_004d513c = 0;
        DAT_0058ed2e = 0;
        uVar3 = 0x35;
      }
      else {
        DAT_004d59a8 = '\0';
        uVar3 = 0x35;
      }
    }
    else {
      if ((DAT_004d5a50 != 8) && (DAT_004d5a50 != 4)) {
        FUN_004152c0();
        FUN_0048e0f7();
        FUN_0048d2e7(DAT_004d5c28);
        FUN_0049a8ed();
        local_10.left = 0;
        local_10.top = 0;
        local_10.bottom = 0x1e0;
        local_10.right = 0x280;
        FUN_0049a9e7(&local_10);
        FUN_00493784(local_10.left,local_10.top,local_10.right,local_10.bottom,2,0,1);
        FUN_0049a93f();
        FUN_0048d32c();
        InvalidateRect(DAT_004d5978,&local_10,0);
        UpdateWindow(DAT_004d5978);
      }
      _DAT_004d5a54 = FUN_004582e0(s_Game_1_005097c4);
      if ((DAT_004d5a50 != 8) && (DAT_004d5a50 != 4)) {
        FUN_00436070();
        FUN_00436064();
        FUN_00427e5c();
        FUN_00427f04();
        FUN_00415274(DAT_004d5978);
        FUN_00494def(1);
        UpdateWindow(DAT_004d5978);
      }
      FUN_00427ee8();
      iVar2 = FUN_00468898();
      if (iVar2 == 1) {
        SendSlaveInfo();
      }
      else if (iVar2 == 2) {
        if (DAT_004d59a8 != '\0') {
          DAT_004d59a8 = 0;
          return 0x35;
        }
        DAT_004d513c = 0;
        DAT_0058ed2e = 0;
        return 0x35;
      }
      uVar3 = 0x43;
    }
  }
  return uVar3;
}

