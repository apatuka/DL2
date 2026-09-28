// CombatReport @ 00421eb4 size=69 sig=undefined CombatReport() cc=unknown
// callers: FUN_00423a80
// callees: FUN_0043df90,DebugMessage,FUN_0043e590
// strings: \"NULL battle in CombatReport()\"

/* auto-named from string evidence: CombatReport */

void CombatReport(int param_1)

{
  if (param_1 == 0) {
    DebugMessage(s_NULL_battle_in_CombatReport___004b7b86);
  }
  else if ((DAT_004d59b4 != 2) && ((DAT_004d59b8 = 1, param_1 != 0 || (DAT_00583c20 != 0)))) {
    FUN_0043e590(param_1);
    FUN_0043df90(param_1);
  }
  return;
}

