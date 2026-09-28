// FUN_00463da8 @ 00463da8 size=89 sig=undefined FUN_00463da8() cc=unknown
// callers: FUN_00464b90,FUN_00440b68,FUN_0043e058,FUN_0045a91c,FUN_00458d80,FUN_00458c6c,FUN_004812f4,FUN_0044a000,CreateWinGWindow,FUN_00480b80,FUN_0043e0dc,FUN_00458d28,StillPic,FUN_004442dc,FUN_00449db4,FUN_0044ae10,FUN_004691f8
// callees: FUN_00463d00

void FUN_00463da8(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x1c;
  DAT_00583e18 = param_1;
  DAT_00583e04 = *(undefined4 *)(&DAT_0058de1c + iVar1);
  DAT_00583e08 = *(undefined4 *)(&DAT_0058de20 + iVar1);
  DAT_00583e0c = *(undefined4 *)(&DAT_0058de28 + iVar1);
  DAT_00583e10 = *(undefined4 *)(&DAT_0058de2c + iVar1);
  DAT_00583e14 = *(undefined4 *)(&DAT_0058de24 + iVar1);
  FUN_00463d00(0,0,DAT_00583e0c,DAT_00583e10);
  return;
}

