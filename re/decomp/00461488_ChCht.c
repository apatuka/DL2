// ChCht @ 00461488 size=1117 sig=undefined ChCht() cc=unknown
// callers: FUN_0045e7a4,FUN_0047361c,FUN_0045ea44,WaitSync,FUN_00472da4,ChCht,AutoSave,CalculateGameCRC
// callees: CreateFileA,FUN_00460d84,FUN_004a6b48,FUN_0045f5e4,FUN_00460870,FUN_00401830,FUN_00477394,FUN_0045fa4c,FUN_00486964,FUN_0042836c,FUN_004605e0,FUN_00460258,FUN_004a68dc,FUN_0045fa10,FUN_00472fb4,FUN_0045fd04,DeleteFileA,FUN_00416af0,FUN_0045f664,FUN_004050ac,ChCht,FUN_0046136c,FUN_004396a0,FUN_0046c9d8,CloseHandle,FUN_0045fe58,FUN_00488aae,MoveFileA,FUN_00460188,FUN_00461308,sprintf,FUN_0046002c,FUN_004612b0,FUN_00460fa4,FUN_0045ff40,FUN_004238c8
// strings: \"campaign\\\\\"|\"saves\\\\\"|\"ChCht\"|\"%s%03d\"|\"SaveGame\"|\"This scenario map does not have enough shrines to complete the SHRINE WARS victory condition. Are you sure you want to save?\"|\"Save Game Error\"|\"%sBackup.bak\"|\"Unable to save current game.\\nWould you like to try again?\"

/* auto-named from string evidence: ChCht, SaveGame */

undefined4 ChCht(LPCSTR param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  HANDLE hObject;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  LPCSTR pCVar9;
  char *pcVar10;
  char local_328 [260];
  undefined1 local_224 [280];
  undefined1 local_10c [260];
  int local_8;
  
  if (DAT_004d5aa0 != '\0') {
    bVar6 = 0;
    iVar7 = 0;
    pcVar2 = &DAT_0059f161;
    do {
      if (*pcVar2 != '\0') {
        bVar6 = bVar6 | '\x01' << (pcVar2[1] & 0x1fU);
      }
      iVar7 = iVar7 + 1;
      pcVar2 = pcVar2 + 0x2d8;
    } while (iVar7 < 7);
    DAT_00559d9c = 0;
    iVar7 = FUN_00416af0(bVar6);
    iVar8 = 0;
    pcVar2 = &DAT_0059f161;
    do {
      if ((*pcVar2 != '\0') && (iVar7 == pcVar2[1])) {
        FUN_00472fb4(iVar8);
      }
      iVar8 = iVar8 + 1;
      pcVar2 = pcVar2 + 0x2d8;
    } while (iVar8 < 7);
  }
  local_8 = 0;
  if (DAT_0058f1fc == 0) {
    if (DAT_004d5a94 < 1) {
      FUN_004a6b48(local_10c,s_saves__004d1cfd,0x104);
    }
    else {
      FUN_004a6b48(local_10c,s_campaign__004d1d04,0x104);
    }
  }
  else {
    FUN_004a6b48(local_10c,&DAT_004d1cfc,0x104);
  }
  FUN_00488aae(local_10c);
  if (param_1 == (LPCSTR)0x0) {
    sprintf(local_224,s__s_03d_004d1d0e,
            s_ChCht_005099cf + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 6,DAT_0059f154);
    if (DAT_004d5a94 < 1) {
      if (DAT_0058f1fc == 0) {
        FUN_004a68dc(local_224,&DAT_004d1d1f);
      }
      else {
        FUN_004a68dc(local_224,&DAT_004d1d1a);
      }
    }
    else {
      FUN_004a68dc(local_224,&DAT_004d1d15);
    }
    param_1 = (LPCSTR)FUN_004396a0(local_224,&local_8);
    if (param_1 == (LPCSTR)0x0) {
      return 0;
    }
  }
  if (DAT_0058f1fc == 0) {
    DAT_0059f15c = FUN_0046c9d8(10000,s_SaveGame_004d1d24);
    FUN_00477394(DAT_0059f15c);
  }
  if ((DAT_004d5aa0 != '\0') && (local_8 == 0)) {
    iVar7 = 0;
    do {
      if (iVar7 != DAT_0058f1f4) {
        FUN_00401830(iVar7);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 7);
    FUN_004050ac();
    DAT_0059f154 = 1;
    FUN_004238c8();
  }
  if ((((DAT_004d5aa0 != '\0') && (DAT_004d5b00 == '\x02')) && (local_8 == 0)) &&
     ((FUN_00486964(), DAT_0065e420 < DAT_004d5af8 &&
      (iVar7 = FUN_0042836c(PTR_s_Save_Game_Error_005099fc,
                            PTR_s_This_scenario_map_does_not_have_e_00509a1c,0x18,0,0), iVar7 == 2))
     )) {
    return 0;
  }
  if (param_3 != 0) {
    uVar4 = 0xffffffff;
    pCVar9 = param_1;
    do {
      pcVar2 = pCVar9;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar2 = pCVar9 + 1;
      cVar1 = *pCVar9;
      pCVar9 = pcVar2;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar2 = pcVar2 + -uVar4;
    pcVar10 = local_328;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar10 = pcVar10 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar10 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar10 = pcVar10 + 1;
    }
    if (DAT_004d5a94 < 1) {
      if (DAT_0058f1fc == 0) {
        sprintf(param_1,s__sBackup_bak_004d1d2d,s_saves__004d1cfd);
      }
      else {
        sprintf(param_1,s__sBackup_bak_004d1d2d,&DAT_004d1cfc);
      }
    }
    else {
      sprintf(param_1,s__sBackup_bak_004d1d2d,s_campaign__004d1d04);
    }
    DeleteFileA(local_328);
    MoveFileA(param_1,local_328);
  }
  hObject = CreateFileA(param_1,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,4,0x8000000,(HANDLE)0x0);
  if (local_8 == 0) {
    if ((((((hObject != (HANDLE)0xffffffff) && (iVar7 = FUN_0045f5e4(hObject,0), iVar7 != 0)) &&
          ((iVar7 = FUN_0045f664(hObject), iVar7 != 0 &&
           (((iVar7 = FUN_0045fa10(hObject), iVar7 != 0 &&
             (iVar7 = FUN_0045fa4c(hObject), iVar7 != 0)) &&
            (iVar7 = FUN_0045fd04(hObject), iVar7 != 0)))))) &&
         ((iVar7 = FUN_0045fe58(hObject), iVar7 != 0 && (iVar7 = FUN_0045ff40(hObject), iVar7 != 0))
         )) && (iVar7 = FUN_0046002c(hObject), iVar7 != 0)) &&
       ((((iVar7 = FUN_00460188(hObject), iVar7 != 0 && (iVar7 = FUN_00460258(hObject), iVar7 != 0))
         && ((iVar7 = FUN_004605e0(hObject), iVar7 != 0 &&
             (((iVar7 = FUN_00460870(hObject), iVar7 != 0 &&
               (iVar7 = FUN_00460fa4(hObject), iVar7 != 0)) &&
              (iVar7 = FUN_004612b0(hObject), iVar7 != 0)))))) &&
        ((iVar7 = FUN_00461308(hObject), iVar7 != 0 && (iVar7 = FUN_0046136c(hObject), iVar7 != 0)))
        ))) goto LAB_004618d1;
    CloseHandle(hObject);
    if ((param_2 != 0) &&
       (iVar7 = FUN_0042836c(PTR_s_Save_Game_Error_005099fc,
                             PTR_s_Unable_to_save_current_game__Wou_00509a00,0x18,0,0), iVar7 == 6))
    {
      uVar3 = ChCht(param_1,1,0);
      return uVar3;
    }
  }
  else {
    if (((hObject != (HANDLE)0xffffffff) && (iVar7 = FUN_0045f5e4(hObject,1), iVar7 != 0)) &&
       ((iVar7 = FUN_0045fa10(hObject), iVar7 != 0 &&
        ((iVar7 = FUN_00460d84(hObject), iVar7 != 0 && (iVar7 = FUN_00460188(hObject), iVar7 != 0)))
        ))) {
LAB_004618d1:
      CloseHandle(hObject);
      return 1;
    }
    CloseHandle(hObject);
  }
  return 0;
}

