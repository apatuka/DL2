// FUN_0042eff4 @ 0042eff4 size=86 sig=undefined FUN_0042eff4() cc=unknown
// callers: FUN_0042f0c4
// callees: FUN_004493dc,FUN_0044a000,FUN_00482b04,DisableMainInterface,FUN_004a4025

void FUN_0042eff4(void)

{
  FUN_004a4025(DAT_004c3800);
  DAT_004c3800 = 0;
  DAT_004d59b4 = DAT_00557ccc;
  FUN_004493dc(0);
  if ((DAT_004d59b4 == 0x32) && (DAT_004c48a0 != 0)) {
    DisableMainInterface(0);
  }
  if (DAT_004c3814 == '\0') {
    FUN_00482b04();
  }
  FUN_0044a000();
  return;
}

