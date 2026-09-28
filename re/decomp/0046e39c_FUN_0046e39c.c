// FUN_0046e39c @ 0046e39c size=464 sig=undefined FUN_0046e39c() cc=unknown
// callers: FUN_00475198,FUN_00475150
// callees: FUN_0042836c,sprintf,FUN_0044a000,DeleteUnit,FUN_0045add0,_DemolishBuilding,FUN_004780e4,FUN_00478090
// strings: \"The %s colony has given up all claims to the planet.  Their colonists have left.\"|\"Opponent Surrenders\"

void FUN_0046e39c(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined1 local_108 [256];
  int *local_8;
  
  if ((&DAT_0059f161)[param_1 * 0x2d8] != '\0') {
    iVar1 = 0;
    pcVar2 = &DAT_00645376;
    do {
      if ((*pcVar2 != '\0') && (pcVar2[2] == param_1)) {
        DeleteUnit(&DAT_00645370 + iVar1 * 0x2e);
      }
      iVar1 = iVar1 + 1;
      pcVar2 = pcVar2 + 0x5c;
    } while (iVar1 < 0x230);
    pcVar2 = &DAT_005a43f0;
    for (iVar1 = 0; iVar1 <= DAT_004d5b18; iVar1 = iVar1 + 1) {
      if (*pcVar2 == param_1) {
        pcVar2[0x10] = '\0';
        pcVar2[0x11] = '\0';
        *pcVar2 = -1;
        iVar3 = 0;
        local_8 = (int *)(pcVar2 + 0x134);
        do {
          if (*local_8 != 0) {
            _DemolishBuilding(&DAT_0059f160 + param_1 * 0x2d8,&DAT_005a43d0 + iVar1 * 0xadc,iVar3,0)
            ;
          }
          iVar3 = iVar3 + 1;
          local_8 = local_8 + 0xd;
        } while (iVar3 < 0x24);
      }
      pcVar2 = pcVar2 + 0xadc;
    }
    if (((DAT_004d5a50 != 0) && ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03')) &&
       (param_1 != DAT_0058f1f4)) {
      FUN_004780e4(param_1,0);
    }
    (&DAT_0059f161)[param_1 * 0x2d8] = 0;
    if ((DAT_0065e3ac == 0) && (param_1 != DAT_0058f1f4)) {
      sprintf(local_108,PTR_s_The__s_colony_has_given_up_all_c_0050988c,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]]);
      FUN_0042836c(PTR_s_Opponent_Surrenders_00509890,local_108,4,0,5);
    }
    if ((param_1 != DAT_0058f1f4) && (DAT_004d5a50 != 0)) {
      iVar1 = FUN_0045add0();
      if ((iVar1 == 1) && (DAT_0065e3ac == 0)) {
        FUN_00478090();
      }
    }
  }
  FUN_0044a000();
  return;
}

