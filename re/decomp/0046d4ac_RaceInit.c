// RaceInit @ 0046d4ac size=1382 sig=undefined RaceInit() cc=unknown
// callers: WinMain
// callees: FUN_00446b3c,sprintf,FUN_004b02a8,FUN_00427f04,FUN_004050ac,FUN_00401830,FUN_00427ee8,FUN_004634a0,memset,FUN_004ae594,FUN_0042e434,FUN_00436098,CheckDiscovery,FUN_0042e2b8,FUN_0046d2e8,FUN_00484c2c,FUN_00466508,FUN_004360ec,SyncBeginTurn,FUN_0046ca40,FUN_00427eb4,FUN_0042e3e4,FUN_00427a6c,FUN_0042e4c0,FUN_00441128,FUN_004ae5b0
// strings: \"All players are now being synchronized.  This may take some time.  Please wait...\"|\"Re-synching Machines\"|\"New Player\"|\"Please select the territory you want a report on.\\nThis will cost you 25 credits.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Race initialization and landing before turn 1 */

longlong RaceInit(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  short *psVar3;
  short sVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined1 *puVar9;
  int iVar10;
  int iVar11;
  uint local_14;
  
  DAT_004c48a4 = 1;
  DAT_0059f154 = 0;
  PTR_DAT_004d5988 = &DAT_0059f160 + DAT_0058f1f4 * 0x2d8;
  FUN_004ae594(DAT_0059f158);
  if (DAT_004d5a88 == 0) {
    DAT_004d5b10 = FUN_004ae5b0();
    DAT_004d5b14 = FUN_004ae5b0();
  }
  if (DAT_004d5aa0 == '\0') {
    DAT_0059f0fc = 0;
  }
  else {
    DAT_004d5aec = 0;
    iVar11 = 0;
    puVar6 = &DAT_0059f162;
    do {
      *puVar6 = 0xff;
      puVar6[-1] = 0;
      iVar11 = iVar11 + 1;
      puVar6 = puVar6 + 0x2d8;
    } while (iVar11 < 7);
  }
  local_14 = 0;
  pcVar8 = &DAT_0059f161;
  for (iVar11 = 0; iVar11 < DAT_004d5aec; iVar11 = iVar11 + 1) {
    if (iVar11 == DAT_0058f1f4) {
      *pcVar8 = '\x01';
    }
    else if (*pcVar8 == '\0') {
      local_14 = local_14 + 1;
    }
    DAT_0059f0fc = DAT_0059f0fc | '\x01' << ((byte)iVar11 & 0x1f);
    pcVar8 = pcVar8 + 0x2d8;
  }
  puVar6 = &DAT_005a0548;
  puVar7 = &DAT_0052245c;
  puVar9 = &DAT_0059f160;
  for (iVar11 = 0; iVar11 < DAT_004d5aec; iVar11 = iVar11 + 1) {
    *puVar9 = (char)iVar11;
    *(undefined4 *)(puVar9 + 0xc) = 500;
    puVar9[0x3e] = 0;
    puVar9[0xb] = 2;
    *(undefined4 *)(puVar9 + 0x3a) = 0;
    memset(&DAT_0059f3da + iVar11 * 0xb6,0,0x1c);
    puVar1 = puVar7;
    for (iVar10 = 0; iVar10 < DAT_004d5aec; iVar10 = iVar10 + 1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
    puVar9[0x38] = 0x7f;
    if (puVar9[1] == '\0') {
      puVar9[1] = 0x7f;
    }
    if (DAT_004d5aa0 == '\0') {
      puVar9[2] = 0xff;
    }
    *puVar6 = (undefined1)DAT_004d5b0c;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 7;
    puVar9 = puVar9 + 0x2d8;
  }
  if (DAT_004d59b4 == 0x2a) {
    FUN_004360ec();
  }
  FUN_0042e434();
  FUN_0042e3e4();
  if (DAT_004d5aa0 == '\0') {
    FUN_0042e2b8();
  }
  DAT_004d5a7c = 0;
  while ((DAT_004d5a7c == 0 && (DAT_0058f1ec == 0))) {
    FUN_004634a0();
    if ((DAT_004d5aa0 == '\0') && (DAT_0058f1ec == 0)) {
      FUN_00427a6c();
    }
    if ((((DAT_004d5b04 != 0) || (DAT_004d5b00 == '\x02')) && (DAT_004d5a7c != 0)) &&
       ((DAT_0058f1ec == 0 && (DAT_004d5aa0 == '\0')))) {
      DAT_004d5a7c = FUN_00466508();
    }
    if (DAT_004d5aa0 != '\0') {
      DAT_004d5a7c = 1;
    }
  }
  FUN_0042e4c0();
  FUN_00436098();
  if (DAT_0058f1ec == 0) {
    puVar7 = &DAT_005a4d6a;
    for (iVar11 = 0; iVar11 < DAT_004d5b18; iVar11 = iVar11 + 1) {
      iVar10 = FUN_004b02a8(8);
      if (iVar10 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_00484c2c(iVar10);
      }
      *puVar7 = uVar2;
      iVar10 = FUN_004b02a8(8);
      if (iVar10 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_00484c2c(iVar10);
      }
      puVar7[1] = uVar2;
      iVar10 = FUN_004b02a8(8);
      if (iVar10 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_00484c2c(iVar10);
      }
      puVar7[2] = uVar2;
      iVar10 = FUN_004b02a8(8);
      if (iVar10 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_00484c2c(iVar10);
      }
      puVar7[3] = uVar2;
      iVar10 = FUN_004b02a8(8);
      if (iVar10 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_00484c2c(iVar10);
      }
      puVar7[4] = uVar2;
      puVar7 = puVar7 + 0x2b7;
    }
    FUN_00441128();
    if (DAT_004d5aa0 == '\0') {
      _DAT_0059f0ec = FUN_0046ca40();
      _DAT_0059f0ec = _DAT_0059f0ec & 7;
      FUN_00446b3c(&DAT_005a43d0 + *(short *)(PTR_DAT_004d5988 + 6) * 0xadc,0x32,3,1,0x2000);
    }
    iVar11 = 0;
    if (0 < (int)local_14) {
      do {
        sVar4 = 1000;
        iVar10 = 0;
        psVar3 = &DAT_0059f43e;
        for (iVar5 = 1; iVar5 < DAT_004d5aec; iVar5 = iVar5 + 1) {
          if ((*(char *)((int)psVar3 + -5) == '\x7f') &&
             (*(short *)(&DAT_005a4e42 + *psVar3 * 0xadc) < sVar4)) {
            sVar4 = *(short *)(&DAT_005a4e42 + *psVar3 * 0xadc);
            iVar10 = iVar5;
          }
          psVar3 = psVar3 + 0x16c;
        }
        if (iVar10 != 0) {
          (&DAT_0059f161)[iVar10 * 0x2d8] = 3;
          FUN_00401830(iVar10);
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < (int)local_14);
    }
    SyncBeginTurn(DAT_0059f154);
    if (DAT_0058f1ec == 0) {
      if (DAT_0058f1fc != 0) {
        FUN_00427eb4(0,PTR_s_Re_synching_Machines_00509844,
                     PTR_s_All_players_are_now_being_synchr_00509848,0,2);
        FUN_00427f04();
        DAT_004d5a78 = 1;
      }
      pcVar8 = &DAT_0059f161;
      for (iVar11 = 0; iVar11 < DAT_004d5aec; iVar11 = iVar11 + 1) {
        if (*pcVar8 != '\0') {
          if (iVar11 == DAT_0058f1f4) {
            sprintf(&DAT_0059f413 + iVar11 * 0x2d8,s_New_Player_00509804);
          }
          else if ('\x02' < *pcVar8) {
            sprintf(&DAT_0059f413 + iVar11 * 0x2d8,(&PTR_s_Sting_00509938)[pcVar8[1]]);
          }
          sVar4 = *(short *)(pcVar8 + 5);
          FUN_0046d2e8(iVar11,&DAT_005a43d0 + sVar4 * 0xadc);
          if (DAT_004d5aa0 == '\0') {
            CheckDiscovery(&DAT_005a43d0 + sVar4 * 0xadc,iVar11,0x17);
          }
        }
        pcVar8 = pcVar8 + 0x2d8;
      }
      if (DAT_0058f1fc != 0) {
        FUN_00427ee8();
        DAT_004d5a78 = 0;
      }
      if (DAT_004d5aa0 == '\0') {
        FUN_004050ac();
        DAT_004c5b50 = (int)(short)(&DAT_0059f166)[DAT_0058f1f4 * 0x16c];
      }
      else {
        DAT_004c5b50 = 1;
        while ((*(byte *)((int)&DAT_005a43ec + DAT_004c5b50 * 0xadc + 1) & 1) != 0) {
          DAT_004c5b50 = DAT_004c5b50 + 1;
        }
      }
      (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] | 1;
    }
  }
  return (ulonglong)local_14 << 0x20;
}

