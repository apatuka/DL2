// GetNetGameOptions @ 00470554 size=491 sig=undefined GetNetGameOptions() cc=unknown
// callers: WinMain
// callees: FUN_0042836c,strlen,FUN_00471068,FUN_00471634,FUN_00471170,FUN_00457864,FUN_004719a0,PostMessageA
// strings: \".\\\\deadlock.ini\"|\"New Player\"|\"Can't start network game with less than 2 participants.\"|\"Network Error\"|\"Without the CD-ROM, you can not be the master of a multiplayer game.  Please insert it now and click OK to continue, or cancel to quit.\"|\"Deadlock 2 CD-ROM Not Found\"

/* Network game setup (host/join, player name) */

undefined4 GetNetGameOptions(void)

{
  int iVar1;
  int local_32c;
  int local_328;
  undefined1 local_324 [4];
  undefined1 local_320 [92];
  int local_2c4;
  undefined1 local_284 [128];
  undefined1 local_204 [64];
  undefined1 local_1c4 [172];
  undefined1 local_118 [20];
  undefined1 local_104 [260];
  
  if (DAT_004d59a8 != 0) {
    DAT_004d59a8 = 0;
    iVar1 = FUN_00471068(s___deadlock_ini_004d5df4,local_320,local_284,0x80);
    if (iVar1 != 0) {
      if (local_2c4 == 0) {
        iVar1 = FUN_004719a0(s___deadlock_ini_004d5df4,1,&local_328,&local_32c,local_284,0x80,
                             s_New_Player_00509804,0x20,local_204,0x40);
        if ((iVar1 != 0) && (DAT_004d59a8 = 2, local_328 != 0)) {
          DAT_004d59a8 = 0x12;
        }
      }
      else if ((local_2c4 == 2) || (local_2c4 == 1)) {
        local_104[0] = 0;
        iVar1 = FUN_00471170(s___deadlock_ini_004d5df4,local_1c4);
        if ((iVar1 != 0) &&
           ((iVar1 = FUN_00471634(s___deadlock_ini_004d5df4,local_118,local_324,local_104,0x104),
            iVar1 != 0 &&
            (iVar1 = FUN_004719a0(s___deadlock_ini_004d5df4,0,&local_328,&local_32c,local_284,0x80,
                                  s_New_Player_00509804,0x20,local_204,0x40), iVar1 != 0)))) {
          iVar1 = strlen(local_104);
          if (iVar1 == 0) {
            DAT_004d59a8 = 1;
          }
          else {
            DAT_004d59a8 = 4;
          }
          if (local_328 != 0) {
            DAT_004d59a8 = DAT_004d59a8 | 0x10;
          }
        }
      }
    }
    if (local_32c < 2) {
      FUN_0042836c(PTR_s_Network_Error_005092c8,PTR_s_Can_t_start_network_game_with_le_005098f4,4,0,
                   9);
      DAT_004d59a8 = 0;
    }
    while ((DAT_004d59ac == 0 && ((DAT_004d59a8 & 0x10) != 0))) {
      iVar1 = FUN_0042836c(PTR_s_Deadlock_2_CD_ROM_Not_Found_0050989c,
                           PTR_s_Without_the_CD_ROM__you_can_not_b_005098f8,6,0,1);
      if (iVar1 != 1) {
        DAT_004d59a8 = 0;
        PostMessageA(DAT_0058f1a4,0x12,0,0);
        return 0;
      }
      FUN_00457864();
    }
  }
  return 1;
}

