// CreateBrushIndirect @ 004b434d size=6 sig=HBRUSH CreateBrushIndirect(LOGBRUSH * plbrush) cc=__stdcall
// callers: CreateMainWindow
// callees: 

HBRUSH CreateBrushIndirect(LOGBRUSH *plbrush)

{
  HBRUSH pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b434d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateBrushIndirect(plbrush);
  return pHVar1;
}

