// FUN_00415924 @ 00415924 size=2568 sig=undefined FUN_00415924() cc=unknown
// callers: FUN_004163d4
// callees: FUN_00450094,FUN_0049117e,FUN_00450204,FUN_0049eb44,FUN_0044febc,FUN_004a68dc,strlen,FUN_00450320,sprintf,FUN_004500d8,FUN_0044fe1c
// strings: \"%s, %s %d\"|\", and \"|\"o Capture both shrines and their surrounding territories\\n\"|\"%d %s\"|\"*** %s *** Will win in %d turns! ***\\n\"|\"*** %s *** Will win THIS TURN!!! ***\\n\"

void FUN_00415924(void)

{
  char cVar1;
  bool bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int *piVar13;
  undefined4 *puVar14;
  undefined *puVar15;
  undefined4 *puVar16;
  char *pcVar17;
  int local_738;
  int local_734;
  int local_72c;
  int local_724;
  int local_720;
  int *local_71c;
  int *local_718;
  int *local_714;
  char local_710 [152];
  undefined4 local_678 [375];
  undefined1 local_9c [100];
  undefined1 local_38 [40];
  
  puVar14 = &DAT_004b7088;
  puVar16 = local_678;
  for (iVar10 = 0x177; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar16 = *puVar14;
    puVar14 = puVar14 + 1;
    puVar16 = puVar16 + 1;
  }
  FUN_0049eb44(DAT_004b7084,6,1,0xf,0,&DAT_0059f413 + DAT_0058f1f4 * 0x2d8);
  if (DAT_004d5a94 < 1) {
    uVar11 = 0xffffffff;
    pcVar6 = (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8]];
    do {
      pcVar17 = pcVar6;
      if (uVar11 == 0) break;
      uVar11 = uVar11 - 1;
      pcVar17 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar17;
    } while (cVar1 != '\0');
    uVar11 = ~uVar11;
    pcVar6 = pcVar17 + -uVar11;
    pcVar17 = local_710;
    for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
      *(undefined4 *)pcVar17 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar17 = pcVar17 + 4;
    }
    for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
      *pcVar17 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar17 = pcVar17 + 1;
    }
  }
  else {
    iVar10 = (DAT_004d5a94 + -1) % 6 + 1;
    uVar4 = FUN_0049117e(0,0x54415453,0xc);
    sprintf(local_710,s__s___s__d_004b7664,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8]],uVar4,iVar10);
    FUN_0049eb44(DAT_004b7084,0xf,1,0x3c,0,2);
    iVar10 = 0;
    do {
      FUN_0049eb44(DAT_004b7084,iVar10 + 0x4b0,1,0x3c,0,2);
      iVar10 = iVar10 + 1;
    } while (iVar10 < 7);
  }
  FUN_0049eb44(DAT_004b7084,8,1,0xf,0,local_710);
  FUN_0049eb44(DAT_004b7084,10,1,0x46,*(undefined4 *)((int)&DAT_00657df4 + DAT_0058f1f4 * 6),0);
  if (DAT_004d5b00 == '\0') {
    uVar4 = DAT_0065e424;
    uVar5 = FUN_0049117e(0,0x54415453,6);
    sprintf(local_710,uVar5,uVar4);
  }
  else if ((DAT_004d5b00 == '\x01') || (DAT_004d5b00 != '\x02')) {
    pcVar6 = (char *)FUN_0049117e(0,0x54415453,8);
    uVar11 = 0xffffffff;
    do {
      pcVar17 = pcVar6;
      if (uVar11 == 0) break;
      uVar11 = uVar11 - 1;
      pcVar17 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar17;
    } while (cVar1 != '\0');
    uVar11 = ~uVar11;
    pcVar6 = pcVar17 + -uVar11;
    pcVar17 = local_710;
    for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
      *(undefined4 *)pcVar17 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar17 = pcVar17 + 4;
    }
    for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
      *pcVar17 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar17 = pcVar17 + 1;
    }
  }
  else {
    iVar10 = DAT_004d5af8;
    iVar9 = DAT_004d5afc;
    uVar4 = FUN_0049117e(0,0x54415453,7);
    sprintf(local_710,uVar4,iVar10,iVar9);
  }
  FUN_0049eb44(DAT_004b7084,0xc,1,0xf,0,local_710);
  if (DAT_0059f100 != 0) {
    iVar10 = 0;
    puVar15 = &DAT_004c6194;
    do {
      iVar9 = *(int *)(puVar15 + DAT_004d5a94 * 0xd8 + 0xc);
      iVar7 = DAT_004d5a94 * 0xd8 + iVar10 * 0x44;
      piVar8 = (int *)(&DAT_004c61a4 + iVar7);
      local_9c[0] = 0;
      switch(iVar9) {
      case 1:
      case 3:
      case 0xb:
        piVar13 = piVar8;
        for (local_738 = 1; piVar13 = piVar13 + 1, local_738 < *piVar8 + 1;
            local_738 = local_738 + 1) {
          FUN_004a68dc(local_9c,(&PTR_s_ChCh_t_00509038)[*piVar13]);
          if (local_738 < *piVar8) {
            if (iVar9 == 0xb) {
              FUN_004a68dc(local_9c,s___and_004b766e);
            }
            else {
              FUN_004a68dc(local_9c,&DAT_004b7675);
            }
          }
        }
        if (iVar9 == 3) {
          sprintf(local_710,PTR_s_o_Lose_if__s_are_eliminated_00509d88,local_9c);
        }
        else {
          iVar7 = FUN_0044febc(iVar9);
          if (iVar7 == 0) {
            uVar3 = 0x6f;
          }
          else {
            uVar3 = 0x78;
          }
          sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),uVar3,local_9c);
        }
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 2:
        if (DAT_004d5a94 == 0x2a) {
          sprintf(local_710,PTR_s_o_Capture_both_shrines_and_their_00509db4);
        }
        else {
          piVar13 = (int *)(&DAT_004c61ac + iVar7);
          for (local_734 = 2; local_734 < *(int *)(&DAT_004c61a8 + iVar7) + 2;
              local_734 = local_734 + 1) {
            FUN_004a68dc(local_9c,&DAT_005a43d0 + *piVar13 * 0xadc);
            if (local_734 <= *(int *)(&DAT_004c61a8 + iVar7)) {
              FUN_004a68dc(local_9c,s___and_004b766e);
            }
            piVar13 = piVar13 + 1;
          }
          iVar7 = FUN_00450204(iVar9);
          if (iVar7 == 0) {
            uVar3 = 0x6f;
          }
          else {
            uVar3 = 0x78;
          }
          sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),uVar3,local_9c,*piVar8);
        }
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 4:
        sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),
                *(undefined4 *)
                 ((int)&PTR_s_Nothing_004fbbc0 +
                 *(int *)(&DAT_004c61a8 + *piVar8 * 4 + iVar7) * 0x32));
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 7:
      case 10:
        FUN_004a68dc(local_678,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4));
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 8:
        piVar13 = (int *)(&DAT_004c61a4 + DAT_004d5a94 * 0xd8 + iVar10 * 0x44);
        piVar8 = piVar13;
        for (local_72c = 1; local_72c <= *piVar13; local_72c = local_72c + 1) {
          sprintf(local_38,s__d__s_004b767c,piVar8[2],(&PTR_s_credits_00509098)[piVar8[1]]);
          FUN_004a68dc(local_9c,local_38);
          if (local_72c < *piVar13) {
            FUN_004a68dc(local_9c,s___and_004b766e);
          }
          piVar8 = piVar8 + 2;
        }
        iVar7 = FUN_004500d8();
        if (iVar7 == 0) {
          uVar3 = 0x6f;
        }
        else {
          uVar3 = 0x78;
        }
        sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),uVar3,local_9c);
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 9:
        sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),
                *(undefined4 *)(puVar15 + DAT_004d5a94 * 0xd8 + 0x10));
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
        break;
      case 0xc:
        iVar7 = FUN_00450320();
        if (iVar7 != 0) {
          FUN_004a68dc(local_678,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4));
          FUN_004a68dc(local_678,&DAT_004b767a);
        }
        break;
      case 0xd:
        sprintf(local_710,*(undefined4 *)(&DAT_00509d7c + iVar9 * 4),
                *(undefined4 *)(&DAT_004c61a8 + iVar7),*piVar8);
        FUN_004a68dc(local_678,local_710);
        FUN_004a68dc(local_678,&DAT_004b767a);
      }
      iVar10 = iVar10 + 1;
      puVar15 = puVar15 + 0x44;
    } while (iVar10 < 3);
  }
  if (DAT_004d5b00 == '\0') {
    uVar4 = FUN_0049117e(0,0x54415453,9);
    FUN_0049eb44(DAT_004b7084,0xe,1,0xf,0,uVar4);
  }
  else if ((DAT_004d5b00 == '\x01') || (DAT_004d5b00 != '\x02')) {
    FUN_0049eb44(DAT_004b7084,0xe,1,0xf,0,0);
  }
  else {
    uVar4 = FUN_0049117e(0,0x54415453,10);
    FUN_0049eb44(DAT_004b7084,0xe,1,0xf,0,uVar4);
  }
  iVar10 = 0;
  bVar2 = false;
  pcVar17 = &DAT_005a0548;
  local_714 = &DAT_0065e404;
  local_718 = &DAT_0065e3e8;
  local_71c = &DAT_0065e3cc;
  pcVar6 = &DAT_0059f162;
  do {
    cVar1 = *pcVar6;
    if ((1 << ((byte)iVar10 & 0x1f) & (int)DAT_0059f0fc) != 0) {
      FUN_0049eb44(DAT_004b7084,iVar10 + 1000,1,0xf,0,(&PTR_s_ChCh_t_00509038)[cVar1]);
      FUN_0049eb44(DAT_004b7084,iVar10 + 0x4b0,1,0xf,0,(&PTR_s_Hog_Tied_0050911c)[*pcVar17]);
      FUN_0049eb44(DAT_004b7084,iVar10 + 0x514,1,0xf,0,&DAT_0059f413 + iVar10 * 0x2d8);
      if (pcVar6[-1] == '\0') {
        uVar4 = FUN_0049117e(0,0x54415453,0xb);
        FUN_0049eb44(DAT_004b7084,iVar10 + 0x44c,1,0xf,0,uVar4);
      }
      else if (DAT_004d5b00 == '\0') {
        if (0 < *local_71c) {
          FUN_0049eb44(DAT_004b7084,iVar10 + 0x44c,1,0x46,*local_71c,0);
        }
      }
      else if ((DAT_004d5b00 != '\x01') && (DAT_004d5b00 == '\x02')) {
        if (((*local_718 < DAT_004d5af8) ||
            ((iVar9 = FUN_0044fe1c(5), iVar9 != 0 && (iVar10 != DAT_0058f1f4)))) ||
           ((iVar10 == DAT_0058f1f4 && (iVar9 = FUN_00450094(), iVar9 == 0)))) {
          if (0 < *local_718) {
            FUN_0049eb44(DAT_004b7084,iVar10 + 0x44c,1,0x46,*local_718,0);
          }
        }
        else {
          bVar2 = true;
          local_720 = DAT_004d5afc - *local_714;
          sprintf(local_710,&DAT_004b7682,*local_718);
          FUN_0049eb44(DAT_004b7084,iVar10 + 0x44c,1,0xf,0,local_710);
          local_724 = (int)cVar1;
        }
      }
    }
    iVar10 = iVar10 + 1;
    local_714 = local_714 + 1;
    local_718 = local_718 + 1;
    local_71c = local_71c + 1;
    pcVar17 = pcVar17 + 1;
    pcVar6 = pcVar6 + 0x2d8;
  } while (iVar10 < 7);
  if (bVar2) {
    if (local_720 < 2) {
      sprintf(local_710,PTR_s______s_____Will_win_THIS_TURN____005098d4,
              (&PTR_s_ChCh_t_00509038)[local_724]);
    }
    else {
      sprintf(local_710,PTR_s______s_____Will_win_in__d_turns__005098d0,
              (&PTR_s_ChCh_t_00509038)[local_724],local_720);
    }
    FUN_004a68dc(local_678,local_710);
  }
  iVar10 = strlen(local_678);
  if (iVar10 != 0) {
    FUN_0049eb44(DAT_004b7084,0x2c,1,0xf,0,local_678);
  }
  return;
}

