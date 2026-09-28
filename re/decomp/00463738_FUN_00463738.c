// FUN_00463738 @ 00463738 size=53 sig=undefined FUN_00463738() cc=unknown
// callers: FUN_0046cc6c
// callees: GetSystemPaletteEntries,ReleaseDC,GetDC

void FUN_00463738(void)

{
  HDC hdc;
  
  hdc = GetDC((HWND)0x0);
  GetSystemPaletteEntries(hdc,0,10,(LPPALETTEENTRY)&DAT_00583db4);
  GetSystemPaletteEntries(hdc,0xf6,10,(LPPALETTEENTRY)&DAT_00583ddc);
  ReleaseDC((HWND)0x0,hdc);
  return;
}

