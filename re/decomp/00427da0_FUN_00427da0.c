// FUN_00427da0 @ 00427da0 size=143 sig=undefined FUN_00427da0() cc=unknown
// callers: FUN_00427e30
// callees: FUN_0048db5d,FUN_004a2cb5,FUN_00427c40,FUN_0049eb44
// strings: \"Game 1\"

longlong FUN_00427da0(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00427c40();
  iVar1 = FUN_004a2cb5(DAT_004b7d80,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7d80 + 100) == 0)) {
    if (local_4 == 5) {
      FUN_0049eb44(DAT_004b7d80,4,1,0xe,0x3f,s_Game_1_005097c4);
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    }
    if (local_4 == 6) {
      DAT_004d59a4 = 0;
      return 0x600000006;
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

