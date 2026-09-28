// FUN_0046cc6c @ 0046cc6c size=54 sig=undefined FUN_0046cc6c() cc=unknown
// callers: WinMain
// callees: CreateGamePalette,LoadSmacker,FUN_00463738,FUN_004418e4
// strings: \"At start\\r\\n\"

undefined4 FUN_0046cc6c(void)

{
  DAT_0058f1c0 = 0x280;
  DAT_0058f1c4 = 0x1e0;
  FUN_004418e4(s_At_start_004d5c51);
  CreateGamePalette();
  FUN_00463738();
  LoadSmacker();
  return 0;
}

