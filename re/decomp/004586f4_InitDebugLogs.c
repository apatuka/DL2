// InitDebugLogs @ 004586f4 size=252 sig=undefined InitDebugLogs() cc=unknown
// callers: WinMain
// callees: fopen,fclose,FUN_004aa0a8
// strings: \"DEBUG.TXT\"|\"Debug Messages Received\\n\"|\"Deadlock 2 v%d.%d%d\\n\\n\"|\"COMBAT.TXT\"|\"Combat Messages Received\\n\"|\"REPLAY.TXT\"|\"Replay Messages Received\\n\"

/* Creates DEBUG.TXT / COMBAT.TXT / REPLAY.TXT */

void InitDebugLogs(void)

{
  int iVar1;
  
  iVar1 = fopen(s_DEBUG_TXT_004d179c,&DAT_004d17a6);
  if (iVar1 != 0) {
    FUN_004aa0a8(iVar1,s_Debug_Messages_Received_004d17a8);
    FUN_004aa0a8(iVar1,s_Deadlock_2_v_d__d_d_004d17c1,(int)DAT_004d5ae8 >> 8,
                 (int)DAT_004d5ae8 >> 4 & 0xf,DAT_004d5ae8 & 0xf);
    fclose(iVar1);
  }
  iVar1 = fopen(s_COMBAT_TXT_004d17d7,&DAT_004d17a6);
  if (iVar1 != 0) {
    FUN_004aa0a8(iVar1,s_Combat_Messages_Received_004d17e2);
    FUN_004aa0a8(iVar1,s_Deadlock_2_v_d__d_d_004d17c1,(int)DAT_004d5ae8 >> 8,
                 (int)DAT_004d5ae8 >> 4 & 0xf,DAT_004d5ae8 & 0xf);
    fclose(iVar1);
  }
  iVar1 = fopen(s_REPLAY_TXT_004d17fc,&DAT_004d17a6);
  if (iVar1 != 0) {
    FUN_004aa0a8(iVar1,s_Replay_Messages_Received_004d1807);
    FUN_004aa0a8(iVar1,s_Deadlock_2_v_d__d_d_004d17c1,(int)DAT_004d5ae8 >> 8,
                 (int)DAT_004d5ae8 >> 4 & 0xf,DAT_004d5ae8 & 0xf);
    fclose(iVar1);
  }
  return;
}

