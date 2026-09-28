// FUN_00471634 @ 00471634 size=874 sig=undefined FUN_00471634() cc=unknown
// callers: GetNetGameOptions,FUN_004684d0
// callees: FUN_00471028,FUN_00470fc0
// strings: \"World\"|\"small\"|\"medium\"|\"Map File\"|\"Color\"|\"earthlike\"|\"Percent Oceans\"|\"Percent Plains\"|\"Percent Forests\"|\"Percent Swamps\"|\"Percent Mountains\"|\"Percent Wastelands\"

bool FUN_00471634(undefined4 param_1,int param_2,int *param_3,undefined1 *param_4,undefined4 param_5
                 )

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined **ppuVar6;
  bool bVar7;
  bool bVar8;
  char local_20 [23];
  char local_9;
  int local_8;
  
  iVar2 = FUN_00470fc0(PTR_s_World_004d5f64,PTR_s_Type_004d5fb8,local_20,0x14,param_1);
  bVar8 = false;
  if (iVar2 != 0) {
    bVar8 = false;
    iVar2 = 0;
    ppuVar6 = &PTR_s_small_004d6030;
    do {
      pcVar3 = local_20;
      pcVar5 = *ppuVar6;
      do {
        if (*pcVar3 != *pcVar5) goto LAB_00471692;
        bVar7 = true;
        if (*pcVar3 == '\0') break;
        pcVar1 = pcVar3 + 1;
        if (*pcVar1 != pcVar5[1]) goto LAB_00471692;
        pcVar3 = pcVar3 + 2;
        pcVar5 = pcVar5 + 2;
        bVar7 = *pcVar1 == '\0';
      } while (!bVar7);
      if (bVar7) {
        bVar8 = true;
        break;
      }
LAB_00471692:
      iVar2 = iVar2 + 1;
      ppuVar6 = ppuVar6 + 1;
    } while (iVar2 < 5);
    if (bVar8 != false) {
      *param_3 = iVar2;
    }
  }
  if ((bVar8 != false) && (*param_3 == 4)) {
    iVar2 = FUN_00470fc0(PTR_s_World_004d5f64,PTR_s_Map_File_004d5fdc,param_4,param_5,param_1);
    if (iVar2 == 0) {
      iVar2 = 1;
      *param_4 = 0;
    }
    iVar4 = 0;
    if (iVar2 != 0) {
      iVar4 = FUN_00471028(PTR_s_World_004d5f64,PTR_DAT_004d5fbc,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar4 != 0) {
      *(undefined1 *)(param_2 + 10) = (undefined1)local_8;
      *(undefined1 *)(param_2 + 0xb) = (undefined1)local_8;
      if ((*(char *)(param_2 + 10) < '\x14') || ('(' < *(char *)(param_2 + 10))) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00470fc0(PTR_s_World_004d5f64,PTR_s_Color_004d5fc0,local_20,0x14,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      bVar8 = false;
      ppuVar6 = &PTR_s_earthlike_004d6044;
      for (local_9 = '\0'; local_9 < '\a'; local_9 = local_9 + '\x01') {
        pcVar3 = local_20;
        pcVar5 = *ppuVar6;
        do {
          if (*pcVar3 != *pcVar5) goto LAB_00471793;
          bVar7 = true;
          if (*pcVar3 == '\0') break;
          pcVar1 = pcVar3 + 1;
          if (*pcVar1 != pcVar5[1]) goto LAB_00471793;
          pcVar3 = pcVar3 + 2;
          pcVar5 = pcVar5 + 2;
          bVar7 = *pcVar1 == '\0';
        } while (!bVar7);
        if (bVar7) {
          bVar8 = true;
          break;
        }
LAB_00471793:
        ppuVar6 = ppuVar6 + 1;
      }
      if (bVar8) {
        *(char *)(param_2 + 0xc) = local_9;
      }
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Oceans_004d5fc4,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (0x4b < local_8)) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      *(undefined1 *)(param_2 + 0xd) = (undefined1)local_8;
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Plains_004d5fc8,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (100 < local_8)) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      *(undefined1 *)(param_2 + 0xe) = (undefined1)local_8;
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Forests_004d5fcc,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (100 < local_8)) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      *(undefined1 *)(param_2 + 0xf) = (undefined1)local_8;
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Swamps_004d5fd0,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (100 < local_8)) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      *(undefined1 *)(param_2 + 0x10) = (undefined1)local_8;
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Mountains_004d5fd4,&local_8,param_1);
    }
    bVar8 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (100 < local_8)) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      *(undefined1 *)(param_2 + 0x11) = (undefined1)local_8;
    }
    iVar2 = 0;
    if (bVar8) {
      iVar2 = FUN_00471028(PTR_s_World_004d5f64,PTR_s_Percent_Wastelands_004d5fd8,&local_8,param_1);
    }
    bVar7 = false;
    if (iVar2 != 0) {
      if ((local_8 < 0) || (100 < local_8)) {
        bVar7 = false;
      }
      else {
        bVar7 = true;
      }
      *(undefined1 *)(param_2 + 0x12) = (undefined1)local_8;
    }
    bVar8 = false;
    if (bVar7) {
      bVar8 = (int)*(char *)(param_2 + 0xd) + (int)*(char *)(param_2 + 0xe) +
              (int)*(char *)(param_2 + 0xf) + (int)*(char *)(param_2 + 0x10) +
              (int)*(char *)(param_2 + 0x11) + (int)*(char *)(param_2 + 0x12) == 100;
    }
  }
  return bVar8;
}

