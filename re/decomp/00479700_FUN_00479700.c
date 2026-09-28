// FUN_00479700 @ 00479700 size=633 sig=undefined FUN_00479700() cc=unknown
// callers: FUN_00468ea4
// callees: sprintf,FUN_004aa418,FUN_00427ee8,memset,FUN_00479050,fclose,fopen,FUN_004779c0,ResetNetGame,FUN_004aa994,FUN_00427f30,FUN_00427f04,FUN_004aa48c,BroadcastBlock,wsprintfA,fread,FUN_0042836c,FUN_00427e80
// strings: \"Sending Game Data\\r%d%% complete\"|\"Load MultiPlayer Game\"|\"Could not open file %s.\"|\"Load Game Error\"

undefined4 FUN_00479700(void)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint local_70;
  undefined4 local_6c;
  undefined4 local_68;
  uint local_64;
  CHAR local_60 [80];
  
  if (DAT_0058ed2e == '\0') {
    uVar1 = 0;
  }
  else {
    sprintf(local_60,PTR_s_Sending_Game_Data__d___complete_00509c34,0);
    FUN_00427e80(0,PTR_s_Load_MultiPlayer_Game_00509c30,local_60,0,2);
    FUN_00427f04();
    iVar2 = fopen(&DAT_0058ed2e,&DAT_004dc387);
    if (iVar2 == 0) {
      wsprintfA(local_60,PTR_s_Could_not_open_file__s__00509a04,&DAT_0058ed2e);
      FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_60,4,0,0);
      uVar1 = 0;
    }
    else {
      DAT_004d59a4 = DAT_004d59a4 | 0x2000;
      FUN_004aa418(iVar2,0,2);
      local_70 = FUN_004aa48c(iVar2);
      FUN_004aa994(iVar2);
      DAT_006535f4 = 0;
      DAT_006535f8 = local_70;
      FUN_004779c0(DAT_0058f1f4,0x39,0,(int)local_70 >> 0x10,local_70 & 0xffff,0,0);
      while (0 < (int)local_70) {
        local_6c = 0x400;
        puVar3 = &local_70;
        if (0x3ff < (int)local_70) {
          puVar3 = &local_6c;
        }
        iVar4 = fread(&DAT_0065363c,1,*puVar3,iVar2);
        if (iVar4 != 0) {
          memset(&DAT_00653a4c,0,0x610);
          local_68 = 0x400;
          puVar3 = &local_70;
          if (0x3ff < (int)local_70) {
            puVar3 = &local_68;
          }
          iVar4 = FUN_00479050(&DAT_0065363c,&DAT_00653a4c,*puVar3);
          iVar5 = 0;
          if (0 < iVar4) {
            do {
              BroadcastBlock(&DAT_00653a4c + iVar5,0x3a,0xfe);
              DAT_006535f4 = DAT_006535f4 + 1;
              if ((DAT_006535f4 & 0xf) == 0) {
                sprintf(local_60,PTR_s_Sending_Game_Data__d___complete_00509c34,
                        (int)((DAT_006535f8 - local_70) * 100) / (int)DAT_006535f8);
                FUN_00427f30(local_60);
              }
              iVar5 = iVar5 + 0x40;
            } while (iVar5 < iVar4);
          }
          local_64 = 0x400;
          puVar3 = &local_70;
          if (0x3ff < (int)local_70) {
            puVar3 = &local_64;
          }
          FUN_004779c0(DAT_0058f1f4,0x3c,0,(int)*puVar3 >> 8 & 0xff,*puVar3 & 0xff,0,0);
        }
        local_70 = local_70 - 0x400;
      }
      FUN_004779c0(DAT_0058f1f4,0x3b,0,0,0,0,0);
      fclose(iVar2);
      FUN_00427ee8();
      DAT_004d59a4 = DAT_004d59a4 & 0xffffdfff;
      ResetNetGame(&DAT_0058ed2e);
      uVar1 = 1;
    }
  }
  return uVar1;
}

