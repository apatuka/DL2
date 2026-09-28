// GetNearestPaletteIndex @ 004b42f3 size=6 sig=UINT GetNearestPaletteIndex(HPALETTE h, COLORREF color) cc=__stdcall
// callers: FUN_00464cbc
// callees: 

UINT GetNearestPaletteIndex(HPALETTE h,COLORREF color)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42f3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = GetNearestPaletteIndex(h,color);
  return UVar1;
}

