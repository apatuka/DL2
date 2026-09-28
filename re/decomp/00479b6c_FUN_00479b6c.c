// FUN_00479b6c @ 00479b6c size=630 sig=undefined FUN_00479b6c() cc=unknown
// callers: FUN_00468ea4
// callees: sprintf,FUN_004aa418,FUN_00427ee8,memset,FUN_00479050,fclose,fopen,FUN_004779c0,FUN_004aa994,FUN_00427f30,FUN_00427f04,FUN_004aa48c,BroadcastBlock,wsprintfA,fread,FUN_0042836c,FUN_00427e80
// strings: \"Sending Game Data\\r%d%% complete\"|\"Load Map\"|\"Could not open file %s.\"|\"Load Game Error\"

undefined4 FUN_00479b6c(void)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint local_6c;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  CHAR local_5c [80];
  
  if (DAT_005597d5 == '\0') {
    uVar1 = 0;
  }
  else {
    sprintf(local_5c,PTR_s_Sending_Game_Data__d___complete_00509c34,0);
    FUN_00427e80(0,PTR_s_Load_Map_00509c3c,local_5c,0,2);
    FUN_00427f04();
    iVar2 = fopen(&DAT_005597d5,&DAT_004dc387);
    if (iVar2 == 0) {
      wsprintfA(local_5c,PTR_s_Could_not_open_file__s__00509a04,&DAT_005597d5);
      FUN_0042836c(PTR_s_Load_Game_Error_00509a08,local_5c,4,0,0);
      uVar1 = 0;
    }
    else {
      DAT_004d59a4 = DAT_004d59a4 | 0x2000;
      FUN_004aa418(iVar2,0,2);
      local_6c = FUN_004aa48c(iVar2);
      FUN_004aa994(iVar2);
      DAT_006535f4 = 0;
      DAT_006535f8 = local_6c;
      FUN_004779c0(DAT_0058f1f4,0x50,0,(int)local_6c >> 0x10,local_6c & 0xffff,0,0);
      while (0 < (int)local_6c) {
        local_68 = 0x400;
        puVar3 = &local_6c;
        if (0x3ff < (int)local_6c) {
          puVar3 = &local_68;
        }
        iVar4 = fread(&DAT_0065363c,1,*puVar3,iVar2);
        if (iVar4 != 0) {
          memset(&DAT_00653a4c,0,0x610);
          local_64 = 0x400;
          puVar3 = &local_6c;
          if (0x3ff < (int)local_6c) {
            puVar3 = &local_64;
          }
          iVar4 = FUN_00479050(&DAT_0065363c,&DAT_00653a4c,*puVar3);
          iVar5 = 0;
          if (0 < iVar4) {
            do {
              BroadcastBlock(&DAT_00653a4c + iVar5,0x51,0xfe);
              DAT_006535f4 = DAT_006535f4 + 1;
              if ((DAT_006535f4 & 0xf) == 0) {
                sprintf(local_5c,PTR_s_Sending_Game_Data__d___complete_00509c34,
                        (int)((DAT_006535f8 - local_6c) * 100) / (int)DAT_006535f8);
                FUN_00427f30(local_5c);
              }
              iVar5 = iVar5 + 0x40;
            } while (iVar5 < iVar4);
          }
          local_60 = 0x400;
          puVar3 = &local_6c;
          if (0x3ff < (int)local_6c) {
            puVar3 = &local_60;
          }
          FUN_004779c0(DAT_0058f1f4,0x53,0,(int)*puVar3 >> 8 & 0xff,*puVar3 & 0xff,0,0);
        }
        local_6c = local_6c - 0x400;
      }
      FUN_004779c0(DAT_0058f1f4,0x52,0,0,0,0,0);
      fclose(iVar2);
      FUN_00427ee8();
      DAT_004d59a4 = DAT_004d59a4 & 0xffffdfff;
      uVar1 = 1;
    }
  }
  return uVar1;
}

