// SetTextColor @ 004b428d size=6 sig=COLORREF SetTextColor(HDC hdc, COLORREF color) cc=__stdcall
// callers: FUN_00464cbc,FUN_00464a3c
// callees: 

COLORREF SetTextColor(HDC hdc,COLORREF color)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b428d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = SetTextColor(hdc,color);
  return CVar1;
}

