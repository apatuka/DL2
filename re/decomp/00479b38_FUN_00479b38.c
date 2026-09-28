// FUN_00479b38 @ 00479b38 size=52 sig=undefined FUN_00479b38() cc=unknown
// callers: FUN_004782ec
// callees: FUN_00479a5c,ResetNetGame,DeleteFileA
// strings: \"NetGame.Sav\"

void FUN_00479b38(void)

{
  FUN_00479a5c();
  ResetNetGame(s_NetGame_Sav_004dc304);
  DeleteFileA(s_NetGame_Sav_004dc304);
  DAT_004d59a4 = DAT_004d59a4 & 0xffffbfff;
  DAT_004dc300 = 1;
  return;
}

