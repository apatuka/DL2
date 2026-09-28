// NetStartState @ 0047c450 size=109 sig=undefined NetStartState() cc=unknown
// callers: FUN_004782ec
// callees: FUN_004419c8,FUN_004418ec
// strings: \"NetStartState\"

/* auto-named from string evidence: NetStartState */

void NetStartState(int param_1)

{
  DAT_00654800 = (uint)*(ushort *)(param_1 + 0x18);
  DAT_006541e4 = CONCAT22(*(undefined2 *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c));
  DAT_006541e8 = 0;
  if (DAT_004dc3c4 != 0) {
    FUN_004419c8(DAT_004dc3c4);
  }
  DAT_004dc3c4 = FUN_004418ec(s_NetStartState_004dc41e,DAT_006541e4);
  if (DAT_004dc3c4 != 0) {
    DAT_006541ec = DAT_004dc3c4;
  }
  return;
}

