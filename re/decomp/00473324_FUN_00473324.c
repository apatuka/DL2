// FUN_00473324 @ 00473324 size=691 sig=undefined FUN_00473324() cc=unknown
// callers: FUN_0047361c
// callees: FUN_004732ec,FUN_00405430,FUN_004a6a60,FUN_004732a8,FUN_004166f4,FUN_00473054,FUN_00473280,FUN_004732d0,FUN_00473300,FUN_004730a8,FUN_004ab4c4,FUN_004add90,FUN_0047323c
// strings: \"PILE IT ON\"|\"GREEBLIE\"|\"WALL2WALL\"|\"CHARISMA\"|\"S-MART\"|\"%s %s\"|\"SQUISH\"

void FUN_00473324(void)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 unaff_EBX;
  bool bVar12;
  char local_84 [64];
  undefined1 local_44 [64];
  
  if (((DAT_004d5a50 == 0) && (DAT_004d5a94 == 0)) && ((code *)PTR_FUN_004d02b8 == FUN_00457ac0)) {
    iVar2 = FUN_004166f4(local_84,0x3f);
    if (iVar2 == 5) {
      FUN_004add90(local_84);
      pcVar3 = local_84;
      pcVar4 = local_84;
      pcVar5 = local_84;
      pcVar6 = local_84;
      pcVar7 = local_84;
      pcVar8 = local_84;
      pcVar9 = local_84;
      pcVar10 = local_84;
      pcVar11 = s_PILE_IT_ON_004d63dc;
      do {
        if (*pcVar3 != *pcVar11) goto LAB_004733a8;
        bVar12 = true;
        if (*pcVar3 == '\0') break;
        pcVar1 = pcVar3 + 1;
        if (*pcVar1 != pcVar11[1]) goto LAB_004733a8;
        pcVar3 = pcVar3 + 2;
        pcVar11 = pcVar11 + 2;
        bVar12 = *pcVar1 == '\0';
      } while (!bVar12);
      if (bVar12) {
        unaff_EBX = 1;
      }
      else {
LAB_004733a8:
        pcVar3 = &DAT_004d63e7;
        do {
          if (*pcVar4 != *pcVar3) goto LAB_004733d7;
          bVar12 = true;
          if (*pcVar4 == '\0') break;
          pcVar11 = pcVar4 + 1;
          if (*pcVar11 != pcVar3[1]) goto LAB_004733d7;
          pcVar4 = pcVar4 + 2;
          pcVar3 = pcVar3 + 2;
          bVar12 = *pcVar11 == '\0';
        } while (!bVar12);
        if (bVar12) {
          unaff_EBX = 2;
        }
        else {
LAB_004733d7:
          pcVar3 = s_GREEBLIE_004d63eb;
          do {
            if (*pcVar5 != *pcVar3) goto LAB_00473406;
            bVar12 = true;
            if (*pcVar5 == '\0') break;
            pcVar4 = pcVar5 + 1;
            if (*pcVar4 != pcVar3[1]) goto LAB_00473406;
            pcVar5 = pcVar5 + 2;
            pcVar3 = pcVar3 + 2;
            bVar12 = *pcVar4 == '\0';
          } while (!bVar12);
          if (bVar12) {
            unaff_EBX = 3;
          }
          else {
LAB_00473406:
            pcVar3 = s_WALL2WALL_004d63f4;
            do {
              if (*pcVar6 != *pcVar3) goto LAB_00473435;
              bVar12 = true;
              if (*pcVar6 == '\0') break;
              pcVar4 = pcVar6 + 1;
              if (*pcVar4 != pcVar3[1]) goto LAB_00473435;
              pcVar6 = pcVar6 + 2;
              pcVar3 = pcVar3 + 2;
              bVar12 = *pcVar4 == '\0';
            } while (!bVar12);
            if (bVar12) {
              unaff_EBX = 4;
            }
            else {
LAB_00473435:
              pcVar3 = &DAT_004d63fe;
              do {
                if (*pcVar7 != *pcVar3) goto LAB_00473464;
                bVar12 = true;
                if (*pcVar7 == '\0') break;
                pcVar4 = pcVar7 + 1;
                if (*pcVar4 != pcVar3[1]) goto LAB_00473464;
                pcVar7 = pcVar7 + 2;
                pcVar3 = pcVar3 + 2;
                bVar12 = *pcVar4 == '\0';
              } while (!bVar12);
              if (bVar12) {
                unaff_EBX = 5;
              }
              else {
LAB_00473464:
                pcVar3 = &DAT_004d6402;
                do {
                  if (*pcVar8 != *pcVar3) goto LAB_00473493;
                  bVar12 = true;
                  if (*pcVar8 == '\0') break;
                  pcVar4 = pcVar8 + 1;
                  if (*pcVar4 != pcVar3[1]) goto LAB_00473493;
                  pcVar8 = pcVar8 + 2;
                  pcVar3 = pcVar3 + 2;
                  bVar12 = *pcVar4 == '\0';
                } while (!bVar12);
                if (bVar12) {
                  unaff_EBX = 6;
                }
                else {
LAB_00473493:
                  pcVar3 = s_CHARISMA_004d6409;
                  do {
                    if (*pcVar9 != *pcVar3) goto LAB_004734c2;
                    bVar12 = true;
                    if (*pcVar9 == '\0') break;
                    pcVar4 = pcVar9 + 1;
                    if (*pcVar4 != pcVar3[1]) goto LAB_004734c2;
                    pcVar9 = pcVar9 + 2;
                    pcVar3 = pcVar3 + 2;
                    bVar12 = *pcVar4 == '\0';
                  } while (!bVar12);
                  if (bVar12) {
                    unaff_EBX = 7;
                  }
                  else {
LAB_004734c2:
                    pcVar3 = s_S_MART_004d6412;
                    do {
                      if (*pcVar10 != *pcVar3) goto LAB_004734ee;
                      bVar12 = true;
                      if (*pcVar10 == '\0') break;
                      pcVar4 = pcVar10 + 1;
                      if (*pcVar4 != pcVar3[1]) goto LAB_004734ee;
                      pcVar10 = pcVar10 + 2;
                      pcVar3 = pcVar3 + 2;
                      bVar12 = *pcVar4 == '\0';
                    } while (!bVar12);
                    if (bVar12) {
                      unaff_EBX = 8;
                    }
                    else {
LAB_004734ee:
                      iVar2 = FUN_004a6a60(local_84,&DAT_004d6419,3);
                      pcVar3 = local_84;
                      if (iVar2 == 0) {
                        FUN_004ab4c4(local_84,s__s__s_004d641d,local_44,&DAT_00653438);
                        unaff_EBX = 9;
                      }
                      else {
                        pcVar4 = s_SQUISH_004d6423;
                        do {
                          if (*pcVar3 != *pcVar4) goto LAB_00473555;
                          bVar12 = true;
                          if (*pcVar3 == '\0') break;
                          pcVar5 = pcVar3 + 1;
                          if (*pcVar5 != pcVar4[1]) goto LAB_00473555;
                          pcVar3 = pcVar3 + 2;
                          pcVar4 = pcVar4 + 2;
                          bVar12 = *pcVar5 == '\0';
                        } while (!bVar12);
                        if (bVar12) {
                          unaff_EBX = 0xd;
                        }
                        else {
LAB_00473555:
                          unaff_EBX = 0xffffffff;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else if (iVar2 == 6) {
      return;
    }
    switch(unaff_EBX) {
    default:
      goto switchD_00473561_caseD_0;
    case 1:
      FUN_00473054();
      break;
    case 2:
      FUN_00473280();
      break;
    case 3:
      FUN_0047323c();
      break;
    case 4:
      FUN_004730a8();
      break;
    case 5:
      FUN_004732d0(1);
      break;
    case 6:
      FUN_004732d0(2);
      break;
    case 7:
      FUN_00405430();
      break;
    case 8:
      FUN_004732ec();
      break;
    case 9:
      FUN_00473300();
      break;
    case 0xd:
      FUN_004732a8();
    }
    (&DAT_0059f434)[DAT_0058f1f4 * 0xb6] = 1;
  }
switchD_00473561_caseD_0:
  return;
}

