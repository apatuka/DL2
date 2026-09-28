// FUN_0043a914 @ 0043a914 size=111 sig=undefined FUN_0043a914() cc=unknown
// callers: FUN_0045eadc
// callees: FUN_0049eb44,FUN_00481098

void FUN_0043a914(void)

{
  if ((DAT_004d59b4 == 1) && (DAT_00559da0 != 0)) {
    DAT_00559da0 = 0;
    if (DAT_004d5aa0 == '\0') {
      FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,DAT_004c48a8);
    }
    else {
      FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,DAT_004c48a8);
    }
    FUN_00481098();
  }
  return;
}

