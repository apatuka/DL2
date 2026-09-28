// FUN_00415624 @ 00415624 size=519 sig=undefined FUN_00415624() cc=unknown
// callers: FUN_004158d0
// callees: FUN_00414f04,FUN_004a3de6,FUN_0042836c,FUN_004a2004,FUN_0049b416,FUN_004493dc,FUN_004155e4,FUN_004989cf,FUN_0046ac44,FUN_0046bdfc,sprintf
// strings: \"Morale in %s\"|\"Culture at Maximum\"|\"You may only view the morale of settlements that you own.\"|\"Oolan's Advice\"|\"Territories must have population before they have morale.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00415624(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  undefined1 local_ec [120];
  undefined1 local_74 [52];
  char local_40 [52];
  
  iVar6 = DAT_004c5b50 * 0xadc;
  if ((&DAT_005a4400)[DAT_004c5b50 * 0x56e] == 0) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Territories_must_have_population_00509740,4,0,9
                );
    uVar2 = 0;
  }
  else if (((&DAT_005a4436)[DAT_0058f1f4 + iVar6] == '\x04') || (_DAT_004d5aa0 != 0)) {
    DAT_004b7080 = FUN_004a3de6(0,0x35313944);
    if (DAT_004b7080 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_004493dc(1);
      DAT_00533294 = DAT_004d59b4;
      DAT_004d59b4 = 0xc;
      FUN_00414f04(DAT_004b7080);
      FUN_004a2004(DAT_004b7080);
      FUN_0046ac44(local_ec,DAT_0058f1f4);
      uVar2 = FUN_0046bdfc(&DAT_005a43d0 + iVar6);
      sprintf(local_74,PTR_s_Morale_in__s_00509734,&DAT_005a43d0 + iVar6);
      if (DAT_0058f16c < 0x19) {
        local_40[0] = '\0';
      }
      else {
        uVar4 = 0xffffffff;
        pcVar7 = PTR_s_Culture_at_Maximum_00509738;
        do {
          pcVar8 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar7 = pcVar8 + -uVar4;
        pcVar8 = local_40;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
      }
      iVar3 = FUN_0049b416(3);
      if (iVar3 != 0) {
        *(undefined4 *)(iVar3 + 4) = 0x60;
        *(undefined4 *)(iVar3 + 8) = 0x60;
        *(undefined4 *)(iVar3 + 0xc) = 0x32;
      }
      FUN_004155e4(6,(int)(char)(&DAT_005a43f7)[iVar6],iVar3);
      FUN_004155e4(8,uVar2,iVar3);
      FUN_004155e4(0xb,DAT_0058f154,iVar3);
      FUN_004155e4(0xd,DAT_0058f158,iVar3);
      FUN_004155e4(0xf,DAT_0058f164,iVar3);
      FUN_004155e4(0x11,DAT_0058f160,iVar3);
      FUN_004155e4(0x13,DAT_0058f15c + DAT_0058f168,iVar3);
      FUN_004155e4(0x15,DAT_0058f16c + DAT_0058f170,iVar3);
      FUN_004155e4(0x17,DAT_0058f174,iVar3);
      if (iVar3 != 0) {
        FUN_004989cf(iVar3);
      }
      uVar2 = 1;
    }
  }
  else {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_only_view_the_morale_of_s_0050973c,4,0,
                 9);
    uVar2 = 0;
  }
  return uVar2;
}

