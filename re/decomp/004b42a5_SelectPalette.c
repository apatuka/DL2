// SelectPalette @ 004b42a5 size=6 sig=HPALETTE SelectPalette(HDC hdc, HPALETTE hPal, BOOL bForceBkgd) cc=__stdcall
// callers: FUN_00464cbc,FUN_00463770,FUN_0048b35f,FUN_00464b90,CreateGamePalette,FUN_0048be22,ShutdownGame,FUN_00444398,CreateGamePalette2
// callees: 

HPALETTE SelectPalette(HDC hdc,HPALETTE hPal,BOOL bForceBkgd)

{
  HPALETTE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42a5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SelectPalette(hdc,hPal,bForceBkgd);
  return pHVar1;
}

