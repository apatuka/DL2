// FUN_0045ad98 @ 0045ad98 size=56 sig=undefined FUN_0045ad98() cc=unknown
// callers: FUN_0043baf4,FUN_0045d6a4,FUN_0047361c,FUN_0043be98,FUN_0045dd18
// callees: FUN_0045ac80,FUN_0042836c
// strings: \"You may only view settlements if they are next to your colony, you have a unit spying in them, or you have bought information from the Skirineen.\"|\"Oolan's Advice\"

void FUN_0045ad98(int param_1)

{
  if (*(char *)(param_1 + 0x66 + DAT_0058f1f4) < '\x03') {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_only_view_settlements_if_005096ec,4,0,9
                );
  }
  else {
    FUN_0045ac80();
  }
  return;
}

