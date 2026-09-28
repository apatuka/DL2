// FUN_00471068 @ 00471068 size=263 sig=undefined FUN_00471068() cc=unknown
// callers: GetNetGameOptions,FUN_00468470
// callees: FUN_00471028,FUN_00470fc0
// strings: \"File Type\"|\"saved_game\"|\"map_file\"|\"Version\"

undefined4 FUN_00471068(undefined4 param_1,int param_2,undefined1 *param_3,undefined4 param_4)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined **ppuVar7;
  bool bVar8;
  char local_18 [20];
  
  iVar3 = FUN_00470fc0(PTR_DAT_004d5f5c,PTR_s_File_Type_004d5f6c,local_18,0x14,param_1);
  bVar2 = false;
  if (iVar3 != 0) {
    bVar2 = false;
    iVar3 = 0;
    ppuVar7 = &PTR_s_saved_game_004d5ff4;
    do {
      pcVar4 = local_18;
      pcVar6 = *ppuVar7;
      do {
        if (*pcVar4 != *pcVar6) goto LAB_004710c6;
        bVar8 = true;
        if (*pcVar4 == '\0') break;
        pcVar1 = pcVar4 + 1;
        if (*pcVar1 != pcVar6[1]) goto LAB_004710c6;
        pcVar4 = pcVar4 + 2;
        pcVar6 = pcVar6 + 2;
        bVar8 = *pcVar1 == '\0';
      } while (!bVar8);
      if (bVar8) {
        bVar2 = true;
        break;
      }
LAB_004710c6:
      iVar3 = iVar3 + 1;
      ppuVar7 = ppuVar7 + 1;
    } while (iVar3 < 3);
    if (bVar2) {
      *(int *)(param_2 + 0x5c) = iVar3;
    }
  }
  if ((bVar2) && ((*(int *)(param_2 + 0x5c) == 0 || (*(int *)(param_2 + 0x5c) == 1)))) {
    iVar3 = FUN_00471028(PTR_DAT_004d5f5c,PTR_s_Version_004d5f70,param_2 + 0x58,param_1);
    if (iVar3 == 0) {
      iVar3 = 1;
      *(undefined4 *)(param_2 + 0x58) = 0;
    }
    bVar2 = false;
    if (iVar3 != 0) {
      if ((*(int *)(param_2 + 0x58) < 0) || (0x120 < *(int *)(param_2 + 0x58))) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
    }
  }
  if (bVar2) {
    uVar5 = FUN_00470fc0(PTR_DAT_004d5f5c,PTR_DAT_004d5f74,param_3,param_4,param_1);
  }
  else {
    *param_3 = 0;
    uVar5 = 0;
  }
  return uVar5;
}

