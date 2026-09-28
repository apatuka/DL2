// FUN_00426d54 @ 00426d54 size=356 sig=undefined FUN_00426d54() cc=unknown
// callers: SelectInit,FUN_00426eb8
// callees: sprintf,Sleep,FUN_00426cd8,FUN_0042726c,FUN_00427278,FUN_0042e66c,FUN_0049eb44
// strings: \"Please select landing site for %s colony.\"|\"%s colony leader, please select your landing site.\"|\"Please wait while the %s colony leader chooses a landing site...\"

void FUN_00426d54(void)

{
  FUN_0042e66c((int)(char)(&DAT_0059f162)[DAT_00557788 * 0x2d8]);
  if (DAT_004d5aa0 != '\0') {
    FUN_00426cd8();
    sprintf(&DAT_00557798,PTR_s_Please_select_landing_site_for___005095dc,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_00557788 * 0x2d8]]);
    FUN_0049eb44(DAT_004b7d34,3,1,10,0,0);
    return;
  }
  if (DAT_00557788 == DAT_0058f1f4) {
    FUN_00426cd8();
    sprintf(&DAT_00557798,PTR_s__s_colony_leader__please_select_y_005095bc,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_00557788 * 0x2d8]]);
    FUN_0049eb44(DAT_004b7d34,3,1,10,0,0);
    DAT_004b7d58 = &DAT_00557798;
    FUN_00427278();
    return;
  }
  FUN_00426cd8();
  sprintf(&DAT_00557798,PTR_s_Please_wait_while_the__s_colony_l_005095c0,
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[DAT_00557788 * 0x2d8]]);
  FUN_0049eb44(DAT_004b7d34,3,1,10,1,0);
  DAT_004b7d58 = &DAT_00557798;
  FUN_00427278();
  FUN_0042726c();
  Sleep(1000);
  return;
}

