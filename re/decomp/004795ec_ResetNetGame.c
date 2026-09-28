// ResetNetGame @ 004795ec size=275 sig=undefined ResetNetGame() cc=unknown
// callers: FUN_00479700,FUN_00479b38
// callees: FUN_004780e4,FUN_0046e96c,FUN_0044a000,FUN_0046e9d0,FUN_00479324,WaitSync,FUN_0046e338,FUN_0047958c,FUN_004618e8,FUN_00479134,FUN_00479fec,FUN_0042836c,FUN_00479164
// strings: \"ResetNetGame1\"|\"Your race was not found in this game. you will not be able to continue.\"|\"Net Load Error\"|\"ResetNetGame2\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Resets network game state (ResetNetGame1/2) */

void ResetNetGame(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  
  FUN_00479134();
  FUN_004618e8(param_1,0);
  FUN_00479164();
  iVar2 = 0;
  pcVar1 = &DAT_0059f161;
  do {
    if (*pcVar1 != '\0') {
      *pcVar1 = -1;
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar2 < 7);
  _DAT_004d8258 = 0;
  DAT_0065347c = 0;
  FUN_0046e96c();
  WaitSync(s_ResetNetGame1_004dc314);
  PTR_DAT_004d5988 = &DAT_0059f160 + DAT_0058f1f4 * 0x2d8;
  if (((&DAT_0059f161)[DAT_0058f1f4 * 0x2d8] == -1) &&
     ((&DAT_00653600)[DAT_0058f1f4] == (int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8])) {
    FUN_00479fec(DAT_0058f1f4);
    FUN_00479324();
    WaitSync(s_ResetNetGame2_004dc379);
    FUN_0047958c();
    FUN_0046e338();
    FUN_0046e9d0();
    FUN_0044a000();
  }
  else {
    FUN_0046e9d0();
    FUN_004780e4(DAT_0058f1f4,1);
    FUN_0042836c(s_Net_Load_Error_004dc322,s_Your_race_was_not_found_in_this_g_004dc331,4,0,1);
    DAT_0058f1ec = 1;
  }
  return;
}

