// GetDC @ 004b4191 size=6 sig=HDC GetDC(HWND hWnd) cc=__stdcall
// callers: FUN_00465640,FUN_0048be22,FUN_0048d391,FUN_0048bc0d,FUN_004655b0,FUN_00458a5c,FUN_0048d5c4,WinMain,CreateGamePalette,FUN_0048b35f,FUN_0048b48b,FUN_0048b018,CreateGamePalette2,FUN_00463738,CreateMainWindow
// callees: 

HDC GetDC(HWND hWnd)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4191. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetDC(hWnd);
  return pHVar1;
}

