// ReleaseDC @ 004b40ef size=6 sig=int ReleaseDC(HWND hWnd, HDC hDC) cc=__stdcall
// callers: FUN_00465640,ShutdownGame,FUN_0048be22,FUN_0048d391,FUN_0048bc0d,FUN_004655b0,FUN_00458a5c,FUN_0048d5c4,WinMain,CreateGamePalette,FUN_0048b35f,FUN_0048b48b,FUN_0048b018,FUN_00463738,CreateMainWindow
// callees: 

int ReleaseDC(HWND hWnd,HDC hDC)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40ef. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ReleaseDC(hWnd,hDC);
  return iVar1;
}

