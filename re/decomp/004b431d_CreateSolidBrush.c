// CreateSolidBrush @ 004b431d size=6 sig=HBRUSH CreateSolidBrush(COLORREF color) cc=__stdcall
// callers: FUN_00464a3c,FUN_00464cbc
// callees: 

HBRUSH CreateSolidBrush(COLORREF color)

{
  HBRUSH pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b431d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateSolidBrush(color);
  return pHVar1;
}

