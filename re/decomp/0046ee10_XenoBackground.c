// XenoBackground @ 0046ee10 size=83 sig=undefined XenoBackground() cc=unknown
// callers: FUN_0046f5d4
// callees: FUN_00415274,CreateWindowExA
// strings: \"XenoBackground\"

/* auto-named from string evidence: XenoBackground */

void XenoBackground(void)

{
  if (DAT_004d5974 == (HWND)0x0) {
    DAT_004d5974 = CreateWindowExA(0,s_XenoBackground_004d5958,s_CHECKSUM_SAV_004d5c2c + 0xc,
                                   0x56000000,0,0,DAT_0058f1c0,DAT_0058f1c4,DAT_0058f1a4,(HMENU)0x0,
                                   DAT_0058f19c,(LPVOID)0x0);
    FUN_00415274(DAT_004d5974);
  }
  return;
}

