// FUN_0046a844 @ 0046a844 size=403 sig=undefined FUN_0046a844() cc=unknown
// callers: FUN_004618e8,FUN_004634a0
// callees: FUN_0046a700,FUN_0046a1ac,FUN_00469744,FUN_00469ff4,FUN_0041e8f8,FUN_0042836c,FUN_00469b2c,FUN_004419c8,FUN_0046a020,FUN_004418ec,memset,FUN_0046a39c,FUN_004694c0
// strings: \"Preparing Long Range Scan\"|\"Height Map\"|\"Color Map\"|\"Not enough Memory for world map.\\n\\nTry playing on a smaller world.\"|\"Out of Memory (RAM) Error\"|\"Scanning Terrain\"|\"Detaching Colony Ship\"|\"Colonists Descending Towards Planet\"

void FUN_0046a844(void)

{
  FUN_0041e8f8(PTR_s_Preparing_Long_Range_Scan_00509914);
  DAT_0058f13c = DAT_004d5b1b * 0x20;
  DAT_0058f140 = DAT_004d5b1a * 0x20;
  DAT_0058f144 = DAT_0058f140 * DAT_0058f13c;
  DAT_0058f138 = FUN_004418ec(s_Height_Map_004d57d4,DAT_0058f144 * 2);
  DAT_0058f134 = FUN_004418ec(s_Color_Map_004d57df,DAT_0058f144);
  if ((DAT_0058f134 == 0) || (DAT_0058f138 == 0)) {
    FUN_0042836c(PTR_s_Out_of_Memory__RAM__Error_00509918,
                 PTR_s_Not_enough_Memory_for_world_map__0050991c,4,0,0);
    DAT_0058f1ec = 1;
    if (DAT_0058f134 != 0) {
      FUN_004419c8(DAT_0058f134);
      DAT_0058f134 = 0;
    }
    if (DAT_0058f138 != 0) {
      FUN_004419c8(DAT_0058f138);
      DAT_0058f138 = 0;
      return;
    }
  }
  else {
    FUN_0046a1ac();
    memset(DAT_0058f138,0xffffffff,DAT_0058f144 * 2);
    memset(DAT_0058f134,0,DAT_0058f144);
    if (DAT_0058f1ec == 0) {
      FUN_00469744();
    }
    if (DAT_0058f1ec == 0) {
      FUN_0046a39c();
    }
    if (DAT_0058f1ec == 0) {
      FUN_00469ff4();
    }
    if (DAT_0058f1ec == 0) {
      FUN_004694c0();
    }
    if (DAT_0058f1ec == 0) {
      FUN_0041e8f8(PTR_s_Scanning_Terrain_00509920);
      if (DAT_0058f1ec == 0) {
        FUN_0046a020();
      }
      FUN_0041e8f8(PTR_s_Detaching_Colony_Ship_00509924);
      FUN_00469b2c();
      if (DAT_0058f1ec == 0) {
        FUN_0046a700();
        DAT_0058f1e4 = DAT_0058f138;
        FUN_0041e8f8(PTR_s_Colonists_Descending_Towards_Pla_00509928);
      }
    }
  }
  return;
}

