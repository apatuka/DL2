// DetectsShrine @ 00446c8c size=99 sig=undefined DetectsShrine() cc=unknown
// callers: FUN_004436cc,CheckDiscovery
// callees: DebugMessage
// strings: \"NULL territory in DetectsShrine()\"

/* auto-named from string evidence: DetectsShrine */

undefined4 DetectsShrine(int param_1,int param_2)

{
  if (param_1 == 0) {
    DebugMessage(s_NULL_territory_in_DetectsShrine__004c53c3);
    return 0;
  }
  if (*(char *)(param_1 + 0x21) == '\0') {
    if (param_2 == 0x1e) {
      return 100;
    }
    if (param_2 == 0x21) {
      return 0x32;
    }
  }
  else {
    if ((&DAT_004faf8d)[param_2 * 0x24] != '\x03') {
      return 100;
    }
    if (param_2 == 0x1c) {
      return 0x32;
    }
  }
  return 0;
}

