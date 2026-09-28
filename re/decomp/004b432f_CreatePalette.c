// CreatePalette @ 004b432f size=6 sig=HPALETTE CreatePalette(LOGPALETTE * plpal) cc=__stdcall
// callers: FUN_0048d82a,FUN_0048b35f,CreateGamePalette,CreateGamePalette2
// callees: 

HPALETTE CreatePalette(LOGPALETTE *plpal)

{
  HPALETTE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b432f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreatePalette(plpal);
  return pHVar1;
}

