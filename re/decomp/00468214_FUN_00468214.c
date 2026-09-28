// FUN_00468214 @ 00468214 size=366 sig=undefined FUN_00468214() cc=unknown
// callers: 
// callees: FUN_00458bc8,FUN_00428b48,FUN_004581a8,FUN_0042836c,FUN_0049117e,FUN_004719a0,FUN_0046903c,FUN_00458298,FUN_00458138
// strings: \".\\\\deadlock.ini\"|\"The TCP/IP (Internet) service is not available.  Please exit the game and make sure that you have TCP/IP installed and that it is configured correctly.\"|\"Network Error\"|\"The TCP/IP (Internet) service could not be initialized.  Please exit the game and make sure that your TCP/IP settings are correct.\"

undefined4 FUN_00468214(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_84 [4];
  undefined1 local_80 [128];
  
  iVar1 = FUN_00458bc8();
  if (iVar1 < 3) {
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 4;
    uVar2 = FUN_0049117e(0,0x54415453,3);
    uVar3 = FUN_0049117e(0,0x54415453,2);
    FUN_0042836c(uVar3,uVar2,uVar5,uVar6,uVar7);
    DAT_004d59a8 = 0;
    return 0x35;
  }
  FUN_00458298();
  DAT_004d8264 = 0;
  if (DAT_004d59a8 == 0) {
    iVar1 = FUN_00428b48();
  }
  else {
    DAT_004d5a4c = (uint)((DAT_004d59a8 & 0x10) == 0);
    FUN_004719a0(s___deadlock_ini_004d5277,0,local_84,&DAT_004d5140,local_80,0x80,local_80,0x20,
                 local_80,0x40);
    DAT_004d5a50 = 8;
    uVar4 = FUN_00458138();
    if ((uVar4 & DAT_004d5a50) == 0) {
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_TCP_IP__Internet__service_is_005092cc,4,0,
                   0);
      DAT_004d59a8 = 0;
      return 0x35;
    }
    iVar1 = FUN_004581a8(0,DAT_004d5a50);
    if (iVar1 == 0) {
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_The_TCP_IP__Internet__service_co_005092dc,4,0,
                   0);
      DAT_004d59a8 = 0;
      return 0x35;
    }
    iVar1 = 3;
  }
  if (iVar1 == 3) {
    if (DAT_004d5a4c == 0) {
      if ((DAT_004d513c == 0) && (DAT_004d59a8 == 0)) {
        uVar2 = FUN_0046903c();
      }
      else {
        uVar2 = 0x3b;
      }
    }
    else {
      uVar2 = 0x3f;
    }
  }
  else {
    uVar2 = 0x35;
  }
  return uVar2;
}

